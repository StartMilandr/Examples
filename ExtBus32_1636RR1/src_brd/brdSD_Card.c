#include "brdSD_Card.h"

#define SD_BY_SPI   0
#define SD_BY_SDIO  1

#if SD_BY_SDIO
  // Функции для работы через SDIO
  #include "brdSDIO.h"

  #define SD_DriverInit         BRD_SDIO_Init

  #define SD_PowerOn            BRD_SDIO_PowerOn
  #define SD_PowerOff           BRD_SDIO_PowerOff
  #define SD_SetRateBRG         BRD_SDIO_SetClockBRG

  #define SD_ExecCMD            BRD_SDIO_ExecCMD

  #define SD_WriteBlock         BRD_SDIO_WriteBlock
  #define SD_ReadBlock          BRD_SDIO_ReadBlock
  #define SD_Send_ClockCycles   BRD_SDIO_Send_ClockCycles
  #define SD_StopTransfer       BRD_SDIO_Stop_Transfer  

  #define SD_GetPowerStatus     BRD_SDIO_GetPowerStatus
  #define SD_IsCardInsert       BRD_SDIO_IsCardInsert

  #define SD_RunTimeout         BRD_SDIO_RunTimeout
  #define SD_GetTimeout         BRD_SDIO_GetTimeout


#elif  SD_BY_SPI
  // Функции для работы через SPI
  
#endif


static BRD_SD_ClockCfg SD_ClockConfig;

static uint8_t   CardType, CardInfo[16 + 16 + 4];       // Card type flag, CSD(16), CID(16), OCR(4)
static uint32_t  CardRCA = 0;                           // Relative Card Address
static uint32_t  CardReady;


//  ============= Инициализация ====================

void BRD_SD_Init(BRD_SD_ClockCfg *cfgClock, BRD_SDDrv_Timeouts *cfgTimeouts)
{
  // Инициализация блока SDIO или SPI
  SD_ClockConfig = *cfgClock;
  SD_DriverInit(SD_ClockConfig.SysTimerPeriod_1ms, cfgTimeouts);
}


//  ============= Вспомогательные функции ====================
static void bswap_cp(uint8_t *dst, const uint32_t *src)
{
  uint32_t d = *src;

  *dst++ = (uint8_t)(d >> 24);
  *dst++ = (uint8_t)(d >> 16);
  *dst++ = (uint8_t)(d >> 8);
  *dst++ = (uint8_t)(d >> 0);
}


// Унифицированная функция для посылки CMD и ACMD
bool SD_ExecACMD(uint32_t cmd, uint32_t arg, SD_ResponceLength respLength, uint32_t *response)
{
  SD_ResponceR1 respCMD55;
  BRD_SD_CMD_Result result;
  
  if (cmd & 0x80) 
  {
    //  Переключение карты в режим ожидания приема команды ACMD
    result = SD_ExecCMD(CMD55, CardRCA << 16, SD_Resp_48, &respCMD55.value);
    if (result != BRD_SD_CMD_OK)
      return false;
    
    //  Если карта не вернула статус ожидания APP_CMD - выход
    if (!(respCMD55.bits.SD_R1_APP_CMD))
      return false;
  }  
  
  //  Сама команда Application-Specific Command
  return (SD_ExecCMD(cmd, arg, respLength, response) == BRD_SD_CMD_OK);
}

bool SD_WaitFor_CardStatus(uint32_t statusMask, uint32_t timeout_ms)
{
  uint32_t rc;

  SD_RunTimeout(timeout_ms);
  while (SD_GetTimeout()) 
  {
    //  CMD13 - SEND_STATUS
    if (SD_ExecACMD(CMD13, CardRCA << 16, SD_Resp_48, &rc) && ((rc & statusMask) == statusMask))
      return true;
  }
  return false;
}

bool BRD_SD_IsCardReady(void)
{  
  return CardReady;
}

bool BRD_SD_IsCardInsert(void)
{  
  return SD_IsCardInsert();
}

void SD_Delay_ms(uint32_t delay_ms)
{
  SD_RunTimeout(delay_ms);
  while (SD_GetTimeout());
}

//  ============= SD Card Detect ====================

BRD_SD_Detect_Result  SD_DetectCard(void)
{
  uint32_t cmd, n;
  uint32_t resp[4];
  SD_ResponceR3 respR3;
  SD_ResponceR1 respR1;
  volatile uint32_t ty = 0;
  
  //  Команда карте на переход в состояние IDLE
  SD_ExecACMD(CMD0, 0, SD_Resp_No, resp);				// CMD0 - GO_IDLE_STATE

  CardRCA = 0;
   
  //  Запрос на поддержку интерфейса: 
  //    [11..8] - напряжение питания, 
  //              0001b - [2.7V .. 3.6V]
  //              0010b - LowVoltage (reserved)
  //    [7..0]  - маска проверки, 0x1AA
  SD_RunTimeout(1000);
  if (SD_ExecACMD(CMD8, 0x1AA, SD_Resp_48, resp))       // CMD8 - SEND_IF_COND
  { // Карта Ver2.00 или более новая
    
    // Ответ R7
    // Возвращает маску если поддерживает указанное напряжение 
    if ((resp[0] & 0xFFF) != 0x1AA)
    { // Не поддерживает питание 2.7-3.6V 
      return SD_VER2_RespErr;
    }
    else
    { //  Карта поддерживает питание 2.7-3.6V 
      
      //  Запрос на высылку регистра OCR - Operation Conditions Register:
      //    [0..23] - Окно напряжений питания
      //       [30] - HCS (Host Capacity Support, bit30) - Говорим карте, что поддерживаем высокую емкость.
      //  Ответ R3 - дожидаемся установки старшего бита SD_R3_Ready == 1 - инициализация после PowerUp окончена.
      while (!SD_ExecACMD(ACMD41, 0x40FF8000, SD_Resp_48, &respR3.value) || !(respR3.bits.SD_R3_Ready))   // ACMD41 - SEND_OP_COND (SDC)
      {
        if (!SD_GetTimeout())
          return SD_VER2_READY_OV;
      } 
    
      //  Проверяем бит CCS (Card Capacity Status) в регистер OCR.
      //    CCS = 1 - то это High Capacity SD Memory
      //    CCS = 0 - то это Standard Capacity SD Memory Card      
      ty = respR3.bits.SD_R3_CCS ? CT_SD2|CT_BLOCK : CT_SD2;
    }
  }  
  else 
  { // Карта SD Ver1 или MMC
    //  Запрос на высылку регистра OCR - Operation Conditions Register:
    //    [0..23] - Окно напряжений питания
    if (SD_ExecACMD(ACMD41, 0x00FF8000, SD_Resp_48, resp))    // ACMD41 - SEND_OP_COND (SDC)
    {
      ty = CT_SD1;                  // ACMD41 is accepted -> SDC Ver1
      cmd = ACMD41;                 // ACMD41 - SEND_OP_COND (SDC)
    } 
    else 
    {
      ty = CT_MMC;                  // ACMD41 is rejected -> MMC  
      cmd = CMD1;                   // CMD1 - SEND_OP_COND (MMC)
    }
    
    //  Ответ R3 - дожидаемся установки старшего бита SD_R3_Ready == 1 - инициализация после PowerUp окончена.    
    while (!SD_ExecACMD(cmd, 0x00FF8000, SD_Resp_48, &respR3.value) || !(respR3.bits.SD_R3_Ready))
    {                  
      if (!SD_GetTimeout())
        return SD_VER1_READY_OV;
    };
  }

  //  Карта инициализирована, сохраняем тип карты и регистр OCR
  CardType = ty;
  bswap_cp(&CardInfo[32], resp);
  
  // ---------  Card in READY state  ------------------

  // Получаем регистр CID - Card Identification Data
  //   CMD2 - ALL_SEND_CID
  if (!SD_ExecACMD(CMD2, 0, SD_Resp_138, resp))
    return SD_CMD2_NO_RESP;
  for (n = 0; n < 4; n++) 
    bswap_cp(&CardInfo[n * 4 + 16], &resp[n]);                    // Save CID

  // Получаем относительный адрес RCA - Relative Card Address
  //   CMD3 - SEND_RELATIVE_ADDR
  if (ty & CT_SDC) 
  { 
    if (!SD_ExecACMD(CMD3, 0, SD_Resp_48, resp))        // SD Card
      return SD_CMD3_SD_NO_RESP;
    CardRCA = (resp[0] >> 16);
  } 
  else 
  { 
    if (!SD_ExecACMD(CMD3, 1 << 16, SD_Resp_48, resp))  // MMC Card
      return SD_CMD3_MMC_NO_RESP;
    CardRCA = 1;
  }

  // Получаем регистр CSD - Card Specific Data
  //   CMD9 - SEND_CSD
  if (!SD_ExecACMD(CMD9, CardRCA << 16, SD_Resp_138, resp))
    return SD_CMD9_NO_RESP;
  for (n = 0; n < 4; n++) 
    bswap_cp(&CardInfo[n * 4], &resp[n]);

  // Переключаем карту в состояние Transfer
  // Только одна карта на шине может быть в состоянии Transfer (выбрана активной)
  // Остальные находятся в состоянии Standby. Активация новой карты, переводит текущую в Standby автоматически.
  //    CMD7  - SELECT_CARD
  // Ответ - R1b, идентичен ответу R1 с опциональным сигналом занятости, передаваемым по линии данных выхода карты.
  //   Карта может оказаться занятой внутренней операцией после получения команд, в зависимости от её состояния перед приемом команды. 
  //   Хост должен проверять занятость карты на каждом ответе карты. - TODO!
  if (!SD_ExecACMD(CMD7, CardRCA << 16, SD_Resp_48, resp))
    return SD_CMD7_NO_RESP;

  // ---------  Card in TRANSFER State  ------------------
  
  // Изменение размера блока в 512 байт для карт Standard Capacity
  //   CMD16 - SET_BLOCKLEN
  if (!(ty & CT_BLOCK)) 
  {   
    if (!SD_ExecACMD(CMD16, SD_BLOCK_512, SD_Resp_48, &respR1.value) || (respR1.value & SD_RespR1_All_ErrorsMask))
      return SD_CMD16_NO_RESP;
  }

  if (ty & CT_SDC) 
  { 
    // Устанавливаем шину данных в 4 бита, (после IDLE ширина = 1 бит)
    //   ACMD6 - SET_BUS_WIDTH (SDC)
    if (!SD_ExecACMD(ACMD6, 2, SD_Resp_48, &respR1.value) || (respR1.value & SD_RespR1_All_ErrorsMask))
      return SD_ACMD6_NO_RESP;
  }

  return SD_OK;
}

BRD_SD_Detect_Result BRD_SD_CardDetect(void)
{
  BRD_SD_Detect_Result result;
  
  CardReady = false;
  
  SD_PowerOn();
  //  Частота при инициализации карты 100KHz .. 400KHz
  SD_SetRateBRG(SD_ClockConfig.SD_CLK_BRG_Detect);
  //  Задержка на включение питания не менее чем длительность 74 тактов
  SD_Delay_ms(SD_ClockConfig.SD_PowerOn_Delay_ms);

//	Сами такты подавать видимо не нужно - работает без этого	
//  SD_Send_ClockCycles(74);
  
  //  Опрашиваем карту
  result = SD_DetectCard();
  
  //  Выставляем рабочую скорость обмена
  if (result == SD_OK)
  {
    SD_SetRateBRG(SD_ClockConfig.SD_CLK_BRG_Transfer); 
    CardReady = true;
  }
  else
    SD_PowerOff();

  return result;
}

//  ============= SD Read Data ====================

BRD_SD_RW_Result BRD_SD_CardRead (uint8_t *buff, uint32_t sectorNum, uint8_t  sectorCnt)
{
  uint32_t resp;
  uint32_t cmd;

  if (sectorCnt < 1 || sectorCnt > 127) 
    return SD_RW_PARERR;
  if (!CardReady) 
    return SD_RW_NOTRDY;

  if (!(CardType & CT_BLOCK)) 
    sectorNum *= SD_BLOCK_512;
  if (!SD_WaitFor_CardStatus(SD_State_Msk_Transf, SD_ClockConfig.SD_WaitStatus_Timout_ms))
    return SD_RW_ERROR;

  //  CMD17 - READ_SINGLE_BLOCK
  //  CMD18 - READ_MULTIPLE_BLOCK
  cmd = (sectorCnt > 1) ? CMD18 : CMD17;
  if (SD_ExecACMD(cmd, sectorNum, SD_Resp_48, &resp) && !(resp & SD_RespR1_RW_ErrorsMask)) 
  {
    do 
    {
      if (!SD_ReadBlock(buff, SD_BLOCK_512)) 
        break;
      buff += SD_BLOCK_512;
    } 
    
    while (--sectorCnt);
      SD_Send_ClockCycles(8);
    
    // Stop reading MULTIPLE_BLOCK
    //   CMD12 - STOP_TRANSMISSION
    if (cmd == CMD18)
      SD_ExecACMD(CMD12, 0, SD_Resp_48, &resp);
  }

  SD_StopTransfer();

  return sectorCnt ? SD_RW_ERROR : SD_RW_OK;
}

//  ============= SD Write Data ====================

bool SD_TryWriteBlock(const uint8_t *buff)
{
  if (!SD_WaitFor_CardStatus(SD_State_Msk_Receive | SD_State_Msk_ReadyForData, SD_ClockConfig.SD_WaitStatus_Timout_ms)) 
    return false;
  
  return SD_WriteBlock(buff);
}

BRD_SD_RW_Result BRD_SD_CardWrite (const uint8_t *buff, uint32_t sectorNum, uint8_t  sectorCnt)
{
  uint32_t rc;
  uint32_t cmd;

  if (sectorCnt < 1 || sectorCnt > 127) 
    return SD_RW_PARERR;
  if (!CardReady) 
    return SD_RW_NOTRDY;

  if (!(CardType & CT_BLOCK)) 
    sectorNum *= SD_BLOCK_512;
  if (!SD_WaitFor_CardStatus(SD_State_Msk_Transf, SD_ClockConfig.SD_WaitStatus_Timout_ms))
    return SD_RW_ERROR;

  if (sectorCnt == 1) 
    cmd = CMD24;      // CMD24 - WRITE_BLOCK
  else 
  {
    //  CMD23  - SET_BLK_COUNT (MMC)
    //  ACMD23 - SET_WR_BLK_ERASE_COUNT (SDC)    
    cmd = (CardType & CT_SDC) ? ACMD23 : CMD23;
    if (!SD_ExecACMD(cmd, sectorCnt, SD_Resp_48, &rc) || (rc & SD_RespR1_RW_ErrorsMask)) {
      return SD_RW_ERROR;
    }
    
    cmd = CMD25;      // CMD25 - WRITE_MULTIPLE_BLOCK
  }

  // Send a write command
  if (!SD_ExecACMD(cmd, sectorNum, SD_Resp_48, &rc) || (rc & SD_RespR1_RW_ErrorsMask)) 
    return SD_RW_ERROR;

  while (sectorCnt) 
  {
    if (!SD_TryWriteBlock(buff)) 
      break;
    sectorCnt--; 
    buff += SD_BLOCK_512;
  }

  SD_StopTransfer();
  
  // Stop reading MULTIPLE_BLOCK
  //   CMD12 - STOP_TRANSMISSION
  if (cmd == CMD25 && (CardType & CT_SDC)) 
    SD_ExecACMD(CMD12, 0, SD_Resp_48, &rc);

  return sectorCnt ? SD_RW_ERROR : SD_RW_OK;
}

//  ============= SD Misc Control ====================
BRD_SD_RW_Result BRD_SD_IO_Ctrl (SD_Card_IO_Ctrl ctrl,   void *buff)
{
  BRD_SD_RW_Result res;
  uint8_t b, *ptr = buff;
  uint32_t resp[4], d, *dp, st, ed;


  res = SD_RW_ERROR;

  switch (ctrl) {
    case SDC_CTRL_SYNC :                                                                        // Make sure that all data has been written on the media
      if (SD_WaitFor_CardStatus(SD_State_Msk_Transf, SD_ClockConfig.SD_WaitStatus_Timout_ms))   // Wait for card enters tran state
        res = SD_RW_OK;
      break;

    case SDC_GET_SECTOR_COUNT :                         // Get number of sectors on the disk (DWORD)
      if ((CardInfo[0] >> 6) == 1) 
      {  
        // SDC CSD v2.0
        d = ((uint16_t)CardInfo[8] << 8) + CardInfo[9] + 1;
        *(uint32_t*)buff = d << 10;
      } 
      else 
      {            
        // MMC or SDC CSD v1.0
        b = (CardInfo[5] & 15) + ((CardInfo[10] & 128) >> 7) + ((CardInfo[9] & 3) << 1) + 2;
        d = (CardInfo[8] >> 6) + ((uint16_t)CardInfo[7] << 2) + ((uint16_t)(CardInfo[6] & 3) << 10) + 1;
        *(uint32_t*)buff = d << (b - 9);
      }
      res = SD_RW_OK;
      break;

    case SDC_GET_BLOCK_SIZE :                           // Get erase block size in unit of sectors (DWORD)
      if (CardType & CT_SD2) 
      {  
        // SDC ver 2.00
        *(uint32_t*)buff = 16UL << (CardInfo[10] >> 4);
      } 
      else 
      {          
        // SDC ver 1.XX or MMC
        if (CardType & CT_SD1)  // SDC v1 
          *(uint32_t*)buff = (((CardInfo[10] & 63) << 1) + ((uint16_t)(CardInfo[11] & 128) >> 7) + 1) << ((CardInfo[13] >> 6) - 1);
        else                    // MMC
          *(uint32_t*)buff = ((uint16_t)((CardInfo[10] & 124) >> 2) + 1) * (((CardInfo[11] & 3) << 3) + ((CardInfo[11] & 224) >> 5) + 1);
      }
      res = SD_RW_OK;
      break;

    case SDC_CTRL_ERASE_SECTOR :                        // Erase a block of sectors
      // Check if sector erase can be applied to the card
      if (!(CardType & CT_SDC) || (!(CardInfo[0] >> 6) && !(CardInfo[10] & 0x40))) 
        break; 
      
      dp = buff; 
      st = dp[0]; 
      ed = dp[1];
      
      if (!(CardType & CT_BLOCK))
      {
        st *= SD_BLOCK_512; 
        ed *= SD_BLOCK_512;
      }
      
      if (   SD_ExecACMD(CMD32, st, SD_Resp_48, resp) 
          && SD_ExecACMD(CMD33, ed, SD_Resp_48, resp) 
          && SD_ExecACMD(CMD38,  0, SD_Resp_48, resp) 
          && SD_WaitFor_CardStatus(SD_State_Msk_Transf, SD_ClockConfig.SD_Erase_Timout_ms))
        res = SD_RW_OK;
      break;

    case SDC_CTRL_POWER :
      switch (ptr[0]) {
      case 0:
        SD_PowerOff();
        res = SD_RW_OK;
        break;
      case 1:
        ptr[1] = (uint8_t) SD_GetPowerStatus();
        res = SD_RW_OK;
        break;
      default :
        res = SD_RW_PARERR;
      }
      break;

    case SDC_MMC_GET_TYPE :             // Get card type flags (1 byte)
      *ptr = CardType;
      res = SD_RW_OK;
      break;

    case SDC_MMC_GET_CSD :              // Get CSD (16 bytes)
      memcpy(buff, &CardInfo[0], 16);
      res = SD_RW_OK;
      break;

    case SDC_MMC_GET_CID :              // Get CID (16 bytes)
      memcpy(buff, &CardInfo[16], 16);
      res = SD_RW_OK;
      break;

    case SDC_MMC_GET_OCR :              // Get OCR (4 bytes)
      memcpy(buff, &CardInfo[32], 4);
      res = SD_RW_OK;
      break;

    case SDC_MMC_GET_SDSTAT :           // Receive SD status as a data block (64 bytes)
      if (CardType & CT_SDC) 
      { 
        // SDC
        if (SD_WaitFor_CardStatus(SD_State_Msk_Transf, SD_ClockConfig.SD_WaitStatus_Timout_ms)) 
        {
          if (SD_ExecACMD(ACMD13, 0, SD_Resp_48, resp)  // Start to read
              && !(resp[0] & SD_RespR1_RW_ErrorsMask)) 
          {
            if (SD_ReadBlock(buff, SD_BLOCK_512)) 
              res = SD_RW_OK;
          }
        }
        SD_StopTransfer();
      }
      break;

    default:
      res = SD_RW_PARERR;
  }

  return res;
}



