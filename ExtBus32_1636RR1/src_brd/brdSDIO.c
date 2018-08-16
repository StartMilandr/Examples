#include "brdSDIO.h"


//  ==================  Настройка пинов ==================
//  При меньшей скорости не проходит даже идентификация
#define PORT_SPEED_SEL  PORT_SPEED_MAXFAST

void SDIO_PortInit(void)
{
	PORT_InitTypeDef GPIOInitStruct;	
	
	//	Clock for PORT
	RST_CLK_PCLKcmd (BRD_SDIO_PORT_CLK, ENABLE);
	
	//  Common params
  GPIOInitStruct.PORT_PULL_DOWN  = PORT_PULL_DOWN_OFF;  
  GPIOInitStruct.PORT_PD_SHM     = PORT_PD_SHM_OFF;
  GPIOInitStruct.PORT_PD         = PORT_PD_DRIVER;
  GPIOInitStruct.PORT_GFEN       = PORT_GFEN_OFF;
  GPIOInitStruct.PORT_SPEED      = PORT_SPEED_SEL;  
  GPIOInitStruct.PORT_MODE       = PORT_MODE_DIGITAL;
  
  //  Custom params
  GPIOInitStruct.PORT_Pin      = BRD_SDIO_INIT_PIN;
  GPIOInitStruct.PORT_PULL_UP  = BRD_SDIO_INIT_PULLUP;
  GPIOInitStruct.PORT_FUNC     = BRD_SDIO_INIT_FUNC;
   
	PORT_Init(BRD_SDIO_INIT_PORT, &GPIOInitStruct);
  
#ifdef  BRD_SDIO_INIT_PORT_1
  GPIOInitStruct.PORT_Pin      = BRD_SDIO_INIT_PIN_1;
  GPIOInitStruct.PORT_PULL_UP  = BRD_SDIO_INIT_PULLUP_1;
  GPIOInitStruct.PORT_FUNC     = BRD_SDIO_INIT_FUNC_1;
   
	PORT_Init(BRD_SDIO_INIT_PORT_1, &GPIOInitStruct);
#endif

#ifdef  BRD_SDIO_INIT_PORT_2
  GPIOInitStruct.PORT_Pin      = BRD_SDIO_INIT_PIN_2;
  GPIOInitStruct.PORT_PULL_UP  = BRD_SDIO_INIT_PULLUP_2;
  GPIOInitStruct.PORT_FUNC     = BRD_SDIO_INIT_FUNC_2;
   
	PORT_Init(BRD_SDIO_INIT_PORT_2, &GPIOInitStruct);
#endif

}


//  ==================  Инициализация и рабочие параметры ==================

//  Таймауты, которые используются при работе с SD картой
static BRD_SDDrv_Timeouts _SDIO_Timeouts;

void BRD_SDIO_Init(uint32_t  periodSysTimer_1ms, BRD_SDDrv_Timeouts *cfgTimeouts)
{ 
  // Настройка выводов SDIO к SD карте
  SDIO_PortInit();
  
  //  Тактирование блока SDIO
  RST_CLK_PCLKcmd (RST_CLK_PCLK_SDIO, ENABLE);
  
  //  Задаем период системного таймера в 1мс
  _SDIO_Timeouts = *cfgTimeouts;
  SysTickStart(periodSysTimer_1ms);
}

void BRD_SDIO_Finit()
{ 
  SysTickStop();
  
  SDIO_Cmd(DISABLE);
  RST_CLK_PCLKcmd (RST_CLK_PCLK_SDIO, DISABLE);
}

//  ==================  Таймауты ==================
//    Параметром BRD_SD_ClockCfg.SysTimerPeriod_1ms необходимо задать период системного таймера в 1мс.

volatile uint32_t DelayInt_ms, DelayExt_ms;

//    Счетчики задержки уменьшаются на 1 мс, с каждым прерыванием. Равенство 0 означает срабатывание таймаута.
void BRD_SDIO_DelayHandler(void)
{
  volatile uint32_t n;
  
	n = DelayExt_ms;
	if (n) 
    DelayExt_ms = --n;
	n = DelayInt_ms;
	if (n) 
    DelayInt_ms = --n;  
}

bool BRD_SDIO_IsCardInsert(void)
{
  // TODO - проверить, работает ли это
  return (BRD_SDIO_PORT_D0->RXTX & BRD_SDIO_PIN_D0) != 0;
}

//  "Встроенный" обработчик системного таймера, применять если в проекте нет своего.
//  Если есть свой обработчки - вызывать в нем BRD_SDIO_DelayHandler(), чтобы таймауты считались.
#if USE_SYS_TIMER_HANDLER
void SysTick_Handler(void)
{
  BRD_SDIO_DelayHandler();
}
#endif

//  --------- Таймауты для внешнего использования в brdSD_Card.c ----------

void BRD_SDIO_RunTimeout(uint32_t timeout_ms)
{
  DelayExt_ms = timeout_ms;
}

uint32_t BRD_SDIO_GetTimeout(void)
{
  return DelayExt_ms;
}


//  ==================  Контроль питания ==================
//  Питание на демоплате всегда включено. Эти функции - условность.
void BRD_SDIO_PowerOn (void)
{
  MDR_SDIO->CR = SDIO_CR__PowerOn;
}

void BRD_SDIO_PowerOff(void)
{
  MDR_SDIO->CR &= ~SDIO_CR_SDE;
}

bool BRD_SDIO_GetPowerStatus(void)
{
  return (MDR_SDIO->CR & SDIO_CR_SDE) == 1;
}


//  ==================  Вспомогательные функции ==================

//    Смена скорости работы с SD картой - частота сигнала CLK
void BRD_SDIO_SetClockBRG(uint32_t clockBRG)
{
  uint32_t regCR = MDR_SDIO->CR;

  if (((regCR >> SDIO_CR_BR_Pos) & 0x7UL) == clockBRG)
    return;
  
  //  Change BRG
  regCR &= ~(7 << SDIO_CR_BR_Pos);
  MDR_SDIO->CR = regCR | (clockBRG << SDIO_CR_BR_Pos);
  
  //  Timeout
  if (_SDIO_Timeouts.SD_ChangeRate_Timout_ms > 0)
    for (DelayInt_ms = _SDIO_Timeouts.SD_ChangeRate_Timout_ms; DelayInt_ms; );  
}


static inline void SDIO_CR_SetMode(uint32_t CR_Flags)
{
  uint32_t regCR = MDR_SDIO->CR;
  regCR &= ~(SDIO_CR__ModeClear);
  MDR_SDIO->CR = regCR | CR_Flags;
}

static inline bool WaitCMDCompleted(uint32_t timeout_ms)
{
  DelayInt_ms = timeout_ms;
  while ((MDR_SDIO->CR & SDIO_CR_WORK2) != 0) 
  { 
    //  Timeout истек, выход с ошибкой
    if (!DelayInt_ms)
      return false;
  }
  
  return true;
}

//  Не уверен что функция WaitCMDStopped() нужна - поэтому использовать по факту
//  У меня работает без нее
#define CHECK_CMD_STOPPED  0

#if CHECK_CMD_STOPPED

  static inline void WaitCMDStopped(void)
  {
    do {
      MDR_SDIO->CR &= ~(SDIO_CR_WORK2 | SDIO_CR_SBITCMD);
    } while (MDR_SDIO->CR & SDIO_CR_WORK2);
  }

  #define WAIT_CMD_STOPPED     WaitCMDStopped
#else
  #define WAIT_CMD_STOPPED     __nop
#endif  

bool BRD_SDIO_Send_ClockCycles(uint32_t clockCycles)
{
  WAIT_CMD_STOPPED();
 
  SDIO_CR_SetMode(SDIO_CR__SendCycles);
  MDR_SDIO->CMDDR  = 0x00FF;
  MDR_SDIO->CMD_TRANSFER = clockCycles;          // Количество циклов
  MDR_SDIO->CMDCRC = 0x00000000;

  MDR_SDIO->CR |= SDIO_CR_WORK2;

  if (!WaitCMDCompleted(_SDIO_Timeouts.SD_SendCMD_Timout_ms))
    return false;
  
  MDR_SDIO->CR &= ~SDIO_CR_DIRCMD;              // Command RX
  return true;
}

void BRD_SDIO_Stop_Transfer (void)
{
  MDR_SDIO->CR &= 0xFFFE07FF;                 // Disable SDIO interrupt
  MDR_SDIO->CR &= 0xFFFFFFF7;                 // Stop SDIO data transfer
}


//  ============= SD Exec Command ====================
#define SD_TX_BIT   0x40

BRD_SD_CMD_Result BRD_SDIO_SendCMD(uint32_t cmd, uint32_t arg)
{
  cmd &= 0x7F;

  WAIT_CMD_STOPPED();

  SDIO_CR_SetMode(SDIO_CR__SendCMD);
  //  Запись команды с аргументом
  MDR_SDIO->CMDDR  = ((cmd | SD_TX_BIT) & 0x0000007F) |
                        (arg >> 16 & 0x0000FF00) |
                        (arg       & 0x00FF0000) |
                        (arg << 16 & 0xFF000000) ;
  MDR_SDIO->CMDDR  = arg & 0x000000FF;
  MDR_SDIO->CMDCRC = 0x00000000;
  MDR_SDIO->CMD_TRANSFER = SD_CMD_LEN;
  MDR_SDIO->CR |= SDIO_CR_WORK2;                                //  Запуск
  
  //  Ожидание окончания передачи c таймаутом
  if (!WaitCMDCompleted(_SDIO_Timeouts.SD_SendCMD_Timout_ms))
    return BRD_SD_CMD_TimeoutSend;
  
  // Передача закончена
  return BRD_SD_CMD_OK;
}

BRD_SD_CMD_Result BRD_SDIO_ReadResponce(SD_ResponceLength respLength, uint32_t *response)
{
  uint32_t tmpBuff[5];
  
  //  Чтение ответа от SD карты
  SDIO_CR_SetMode(SDIO_CR__ReadResp);
  
  MDR_SDIO->CMD_TRANSFER = (uint32_t) respLength;
  MDR_SDIO->CMDCRC = 0x00000000;
  MDR_SDIO->CR |= SDIO_CR_WORK2;

  //  Ожидание приема ответа с таймаутом
  if (!WaitCMDCompleted(_SDIO_Timeouts.SD_ReadResp_Timout_ms))
  {
    // Принудительная остановка транзакции
    MDR_SDIO->CR &= ~(SDIO_CR_WORK2 | SDIO_CR_SBITCMD);
    return BRD_SD_CMD_TimeoutSend;
  }

  //  Чтение принятых данных из FIFO
  tmpBuff[0] = MDR_SDIO->CMDDR;                 // Read the response words 0
  tmpBuff[1] = MDR_SDIO->CMDDR;                 // Read the response words 1

  response[0] = ((tmpBuff[0]<<8) & 0xFFFFFF00) | ((tmpBuff[1]>>8) & 0x000000FF);
  if (respLength == SD_Resp_138) 
  {
    tmpBuff[2] = MDR_SDIO->CMDDR;               // Read the response words 2
    tmpBuff[3] = MDR_SDIO->CMDDR;               // Read the response words 3
    tmpBuff[4] = MDR_SDIO->CMDDR;               // Read the response words 4
    
    response[1] = ((tmpBuff[1]<<8) & 0xFFFFFF00) | ((tmpBuff[2]>>8) & 0x000000FF);
    response[2] = ((tmpBuff[2]<<8) & 0xFFFFFF00) | ((tmpBuff[3]>>8) & 0x000000FF);
    response[3] = ((tmpBuff[3]<<8) & 0xFFFFFF00) | ((tmpBuff[4]>>8) & 0x000000FF);
  }
  
  return BRD_SD_CMD_OK;
}

BRD_SD_CMD_Result BRD_SDIO_ExecCMD(uint32_t cmd, uint32_t arg, SD_ResponceLength respLength, uint32_t *response)
{
  BRD_SD_CMD_Result result;
  
  result = BRD_SDIO_SendCMD(cmd, arg);
  if (result == BRD_SD_CMD_OK)
  {
    if (respLength == SD_Resp_No)
      BRD_SDIO_Send_ClockCycles(8);
    else
    {
      //  Задержка после сброса SDIO_SD_CR_WORK2 перед чтением ответа от SD карты - 2мс
      if (_SDIO_Timeouts.SD_BeforeRead_Delay_ms > 0)
        for (DelayInt_ms = _SDIO_Timeouts.SD_BeforeRead_Delay_ms; DelayInt_ms; );
    
      //  Чтение ответа от карты
      result = BRD_SDIO_ReadResponce(respLength, response);
    }
  }
   
  return result;
}

//  ============= SD Read Block ====================

#define READ_BY_ASM     1

__ASM void __get_DAT(volatile uint32_t* adr_datdr, uint8_t* adr_buff)
{
    ldr r0, [r0]
    rev r0, r0
    str r0, [r1]

    bx lr
}

bool BRD_SDIO_ReadBlock(uint8_t *buff, uint32_t blockSize)
{
  uint32_t i;
  volatile uint32_t tmp_DATDR;

  SDIO_CR_SetMode(SDIO_CR__ReadBlock);
  
  MDR_SDIO->DAT_TRANSFER = blockSize * 8 + (16 + 1);     // Length
  MDR_SDIO->DAT0CRC = 0x00000000;
  MDR_SDIO->DAT1CRC = 0x00000000;
  MDR_SDIO->DAT2CRC = 0x00000000;
  MDR_SDIO->DAT3CRC = 0x00000000;
  MDR_SDIO->CR |= SDIO_CR_WORK1;                         //  Start

  i = 0;
  DelayInt_ms = _SDIO_Timeouts.SD_ReadBlock_Timout_ms;
  while ((MDR_SDIO->CR & SDIO_CR_WORK1) != 0) 
  { 
    // Выход по таймауту
    if (!DelayInt_ms)
    {
      MDR_SDIO->CR &= ~(SDIO_CR_WORK1 | SDIO_CR_SBITDAT);
      return false;
    }
    if (((MDR_SDIO->SR & 0x02) == 0) && (i < blockSize))
    {
#ifdef READ_BY_ASM
      __get_DAT(&MDR_SDIO->DATDR, &buff[i]);
#else
      tmp_DATDR = SDIO->SD_DATDR;
      buff[i]   = (BYTE)(tmp_DATDR>>24 & 0x000000FF);     // Read the response words 
      buff[i+1] = (BYTE)(tmp_DATDR>>16 & 0x000000FF);     // Read the response words 
      buff[i+2] = (BYTE)(tmp_DATDR>>8  & 0x000000FF);     // Read the response words 
      buff[i+3] = (BYTE)(tmp_DATDR     & 0x000000FF);     // Read the response words      
#endif
      i = i + 4;
    }
  }

  while (i < blockSize)
  {
#ifdef READ_BY_ASM
    __get_DAT(&MDR_SDIO->DATDR, &buff[i]);
#else
    tmp_DATDR = SDIO->SD_DATDR;
    buff[i]   = (BYTE)(tmp_DATDR>>24 & 0x000000FF);     // Read the response words 
    buff[i+1] = (BYTE)(tmp_DATDR>>16 & 0x000000FF);     // Read the response words 
    buff[i+2] = (BYTE)(tmp_DATDR>>8  & 0x000000FF);     // Read the response words 
    buff[i+3] = (BYTE)(tmp_DATDR     & 0x000000FF);     // Read the response words      
#endif
    i = i + 4;
  }
  tmp_DATDR = MDR_SDIO->DATDR;
  tmp_DATDR = MDR_SDIO->DATDR;
  tmp_DATDR = MDR_SDIO->DATDR;

  return true;
}


//  ============= SDIO Write Block ====================

bool BRD_SDIO_WriteBlock(const uint8_t *buff)
{
  uint32_t i;

  SDIO_CR_SetMode(SDIO_CR__WriteBlock);
  
  MDR_SDIO->DAT0CRC = 0x00000000;
  MDR_SDIO->DAT1CRC = 0x00000000;
  MDR_SDIO->DAT2CRC = 0x00000000;
  MDR_SDIO->DAT3CRC = 0x00000000;
  
  i = 0;
  while (i < 512)
  {
    MDR_SDIO->DATDR = (uint32_t)(buff[i] | buff[i+1] << 8 | buff[i+2] << 16 | buff[i+3] << 24);
    i = i + 4;
  }
  MDR_SDIO->DAT_TRANSFER = 512 * 8  + (16 + 1);       // Set length
  MDR_SDIO->CR |= SDIO_CR_WORK1;                      // Initiate data transaction

  // Wait for end of the resp transaction  
  DelayInt_ms = _SDIO_Timeouts.SD_WriteBlock_Timout_ms;
  while ((MDR_SDIO->CR & SDIO_CR_WORK1) != 0) 
  {
    if (!DelayInt_ms) 
    {
      MDR_SDIO->CR &= ~(SDIO_CR_WORK1 | SDIO_CR_SBITDAT);
      return 0;
    }
    if ((i == 512) && !(MDR_SDIO->SR & SDIO_SR_FIFODAT_FULL))
    {
      MDR_SDIO->DATDR = 0x00000000;
      i = i + 2;
    }
  }
  
  MDR_SDIO->CR &= ~SDIO_CR_DIRDATA;                   // DATA RX

  DelayInt_ms = _SDIO_Timeouts.SD_WriteBlock_Timout_ms;
  BRD_SDIO_Send_ClockCycles(8);
  while ((BRD_SDIO_PORT_D0->RXTX & BRD_SDIO_PIN_D0) == 0) 
  {
    BRD_SDIO_Send_ClockCycles(8);
    if (!DelayInt_ms)  
      return false;
  }

  return true;
}
