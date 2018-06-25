#include "brdIWDT.h"

void BRD_IWDT_Init(BrdIWDT_Obj *Obj)
{
  /* Enables the HSI clock for IWDG */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_IWDG, ENABLE);

  /* Enables write access to IWDG_PR,IWDG_RLR registers */
  IWDG_WriteAccessEnable();

  /* Set IWDG Prescaler value */
  IWDG_SetPrescaler(Obj->Prescaler);
	IWDG_SetReload(Obj->ReloadPeriod);
	IWDG_ReloadCounter();

  /* Start IWDT */
  IWDG_Enable();
}
