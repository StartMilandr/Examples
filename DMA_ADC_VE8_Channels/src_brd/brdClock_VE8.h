#ifndef _BRD_CLOCK_VE8_H
#define _BRD_CLOCK_VE8_H

#include <stdint.h>

//	Analog to VE9x
void BRD_Clock_Init_HSE_PLL(uint32_t PLL_Mul);

void BRD_Clock_Init_HSE0_PLL(uint32_t pll_Q, uint32_t pll_N);
void BRD_Clock_Init_HSE0_60MHz(void);

#endif  //_BRD_CLOCK_VE8_H
