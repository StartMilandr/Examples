#include "brdSysTimer.h"

void SysTickStart(uint32_t ticks)
{
  SysTick->LOAD = ticks-1;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}

void SysTickStop(void)
{
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

