#ifndef _BRD_SD_CARD_H
#define _BRD_SD_CARD_H

#include "SD_Card.h"

typedef enum 
{
  SD_OK,
  SD_VER2_RespErr,      //  Power responce is wrong
  SD_VER2_READY_OV,
  SD_VER1_READY_OV,
  SD_CMD2_NO_RESP,      //  CID Read fault
  SD_CMD3_SD_NO_RESP,   //  RCA Read fault - SD
  SD_CMD3_MMC_NO_RESP,  //  RCA Read fault - MMS
  SD_CMD9_NO_RESP,      //  CSD Read fault (Card Specific Data)
  SD_CMD7_NO_RESP,      //  SELECT_CARD fault
  SD_CMD16_NO_RESP,     //  SET_BLOCKLEN 512 fault
  SD_ACMD6_NO_RESP      //  SET_BUS_WIDTH = 4 fault 
} BRD_SD_Detect_Result;

typedef enum
{
  SD_RW_OK = 0,		      // 0: Successful
	SD_RW_ERROR,		      // 1: R/W Error
	SD_RW_WRPRT,		      // 2: Write Protected
	SD_RW_NOTRDY,		      // 3: Not Ready
	SD_RW_PARERR		      // 4: Invalid Parameter
} BRD_SD_RW_Result;


//  Задание рабочих параметров
void BRD_SD_Init(BRD_SD_ClockCfg *cfgClock, BRD_SDDrv_Timeouts *cfgTimeouts);

//  Работа с картой
BRD_SD_Detect_Result  BRD_SD_CardDetect(void);
BRD_SD_RW_Result      BRD_SD_CardRead (uint8_t *buff, uint32_t sectorNum, uint8_t  sectorCnt);
BRD_SD_RW_Result      BRD_SD_CardWrite (const uint8_t *buff, uint32_t sectorNum, uint8_t  sectorCnt);
BRD_SD_RW_Result      BRD_SD_IO_Ctrl (SD_Card_IO_Ctrl ctrl,   void *buff);
bool                  BRD_SD_IsCardReady(void);
bool                  BRD_SD_IsCardInsert(void);


//  Для отладки
bool SD_WaitFor_CardStatus(uint32_t statusMask, uint32_t timeout_ms);

#endif //_BRD_SD_CARD_H
