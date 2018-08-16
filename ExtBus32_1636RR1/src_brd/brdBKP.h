#ifndef BRD_BKP_H
#define BRD_BKP_H

#include <stdint.h>

#include "brdDef.h"
#include "brdUtils.h"

#ifdef USE_BOARD_VE_8 
  #include  <mdr32f8_clkctrl.h>
  #include "spec.h"  
#else  
  #include <MDR32F9Qx_port.h>
  #include <MDR32F9Qx_rst_clk.h>  
#endif

typedef enum {brd_BKP_R0, brd_BKP_R1, brd_BKP_R2, brd_BKP_R3, brd_BKP_R4} BRD_BKP_REG;

void BRD_BKP_Init(void);

void     BRD_BKP_WriteReg(BRD_BKP_REG regInd, uint32_t value);
uint32_t BRD_BKP_ReadReg(BRD_BKP_REG regInd);

void BRD_CallReset(void);

#endif //BRD_BKP_H

