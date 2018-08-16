#include "brdPower.h"


void BRD_Power_Init(BRD_Power_Obj *powerCfg)
{
	//	Clock
	RST_CLK_PCLKcmd (RST_CLK_PCLK_POWER, ENABLE);
	//	Deinit
	POWER_DeInit();
	//	Set Uref Level
	POWER_PVDlevelConfig(powerCfg->LevelPVD);
  POWER_PVBDlevelConfig(powerCfg->LevelPVDBat);
	//	Set INV
  POWER_PVD_INVconfig(powerCfg->EventInvMask, ENABLE);	
	//  PVD_IRQ Ena - moved to BRD_PowerPVD_EnaIRQ
  //POWER_PVD_ITconfig(powerCfg->IrqEnaMask, ENABLE);

  //	ENABLE
	POWER_PVDenable(ENABLE);
	//	Double Clear
	POWER_ClearFlag(POWER_FLAG_PVD | POWER_FLAG_PVBD);
	POWER_ClearFlag(POWER_FLAG_PVD | POWER_FLAG_PVBD);
}

void BRD_Power_InverseEvent(uint32_t EventInvMask)
{
  MDR_POWER->PVDCS ^= EventInvMask; 
}  

void BRD_PowerPVD_EnaIRQ(uint32_t IrqEnaMask, uint32_t enable)
{
  //  PVD_IRQ Enable  
  POWER_PVD_ITconfig(IrqEnaMask, (FunctionalState)enable);

  if (enable)
  {
    NVIC_ClearPendingIRQ(POWER_IRQn);
    NVIC_EnableIRQ(POWER_IRQn);	
  }
  else
  { 
    NVIC_DisableIRQ(POWER_IRQn);
    NVIC_ClearPendingIRQ(POWER_IRQn);
  }    
}

//  //  IRQ Example
//void POWER_IRQHandler(void)
//{
//	//	Clear PendingIRQ
//	NVIC_ClearPendingIRQ(POWER_IRQn);		
//	
//	//	Clear PVD
//	POWER_ClearFlag(POWER_FLAG_PVD | POWER_FLAG_PVBD);		
//	POWER_ClearFlag(POWER_FLAG_PVD | POWER_FLAG_PVBD);
//}


