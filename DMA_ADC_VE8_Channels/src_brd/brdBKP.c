#include "brdBKP.h"

void BRD_CallReset()
{
  SCB->AIRCR = (0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk;
  for(;;) {};  // wait for reset
}

#ifndef USE_BOARD_VE_8

#define BKP_REG0_ADDR     MDR_BKP_BASE

void BRD_BKP_Init(void)
{
  RST_CLK_PCLKcmd (RST_CLK_PCLK_BKP, ENABLE);    
}

void BRD_BKP_WriteReg(BRD_BKP_REG regInd, uint32_t value)
{
  HWREG(BKP_REG0_ADDR + regInd) = value;
}

uint32_t BRD_BKP_ReadReg(BRD_BKP_REG regInd)
{
  return HWREG(BKP_REG0_ADDR + regInd);
}
  
#else
  
void BRD_BKP_Init(void)
{ 
  CLKCTRL_PER0_CLKcmd(CLKCTRL_PER0_CLK_MDR_BKP_EN, ENABLE);
  BKP->KEY = _KEY_;
}

#define BKP_REG0_ADDR     MDR_BKP_BASE

void BRD_BKP_WriteReg(BRD_BKP_REG regInd, uint32_t value)
{
  BKP->REG_xx[regInd] = value;
}

uint32_t BRD_BKP_ReadReg(BRD_BKP_REG regInd)
{
  return BKP->REG_xx[regInd];
}

#endif



