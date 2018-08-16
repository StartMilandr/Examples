#ifndef _BRD_SDIO_H
#define _BRD_SDIO_H

#include <stdbool.h>
#include <string.h>

#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_sdio.h>
#include "brdDef.h"

#include "brdSysTimer.h"
#include "SD_Card.h"


//  Использовать "встроенный" обработчик системного таймера, если в проекте нет своего.
//  Если есть свой обработчик - вызывать в нем BRD_SDIO_DelayHandler(), чтобы таймауты считались.
#define USE_SYS_TIMER_HANDLER   0

#define SDIO_CR__PowerOn      SDIO_CR_SDE | SDIO_CR_CLKOE | SDIO_CR_CRC_EN_DATA
#define SDIO_CR__SendCMD      SDIO_CR_CRC_EN_CMD | SDIO_CR_SBITCMD | SDIO_CR_DIRCMD
#define SDIO_CR__ReadResp     SDIO_CR_CRC_EN_CMD | SDIO_CR_SBITCMD
#define SDIO_CR__SendCycles   SDIO_CR_DIRCMD

#define SDIO_CR__ReadBlock    SDIO_CR_CRC_EN_CMD | SDIO_CR_SBITDAT
#define SDIO_CR__WriteBlock   SDIO_CR_CRC_EN_CMD | SDIO_CR_SBITDAT | SDIO_CR_DIRDATA

#define SDIO_CR__ModeClear   (SDIO_CR_CRC_EN_CMD | SDIO_CR_SBITCMD | SDIO_CR_DIRCMD | SDIO_CR_SBITDAT | SDIO_CR_DIRDATA)

//--------------    SDIO Block Control -----------------

void BRD_SDIO_Init(uint32_t  periodSysTimer_1ms, BRD_SDDrv_Timeouts *cfgTimeouts);
void BRD_SDIO_Finit(void);


//--------------  SD Card Control -----------------

BRD_SD_CMD_Result  BRD_SDIO_ExecCMD(uint32_t cmd, uint32_t arg, SD_ResponceLength respLength, uint32_t *response);

bool BRD_SDIO_ReadBlock(uint8_t *buff, uint32_t blockSize);
bool BRD_SDIO_WriteBlock(const uint8_t *buff);
bool BRD_SDIO_Send_ClockCycles(uint32_t clockCycles);

bool BRD_SDIO_GetPowerStatus(void);
void BRD_SDIO_PowerOn (void);
void BRD_SDIO_PowerOff(void);
void BRD_SDIO_SetClockBRG(uint32_t clockBRG);
void BRD_SDIO_Stop_Transfer(void);
bool BRD_SDIO_IsCardInsert(void);

//  Timeouts
void      BRD_SDIO_RunTimeout(uint32_t timeout_ms);
uint32_t  BRD_SDIO_GetTimeout(void);


//  ОБЯЗАТЕЛЬНО! вызывать обработчик в прерывании от таймера с периодом 1мс
void BRD_SDIO_DelayHandler(void);

//  Пример запуска системного таймера через функцию из brdSysTimer.c
//   SysTickStart(8000000UL/1000UL);                         // 1 ms при HCLK = 8MHz

//-------------   Debug Access-------------
BRD_SD_CMD_Result BRD_SDIO_SendCMD(uint32_t cmd, uint32_t arg);

#endif //_BRD_SDIO_H
