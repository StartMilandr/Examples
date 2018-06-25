#include "brdClock.h"

uint32_t BRD_CPU_CLK = (uint32_t)8000000; 

void BRD_Clock_Init_HSE0_PLL(uint32_t pll_Q, uint32_t pll_N)
{  
    POR_disable();
  
/* Set CLKCTRL to default */
	CLKCTRL_DeInit();
	
	/* Enable HSE0 clock */
	CLKCTRL_HSEconfig(CLKCTRL_HSE0_CLK_ON);
	
	/* Check HSE success, enable PLL0, check PLL0 success, select MAX_CLK src */
	while(CLKCTRL_HSEstatus(CLKCTRL_HSEn_STAT_HSE0_RDY) != SUCCESS){}
	
	/* Select PLL0 clk src, PLL0_N, PLL0_Q to get FINT = FIN*(PLLn_N)/(PLLn_Q+1) */
	CLKCTRL_CPU_PLLconfig(PLL0, CLKCTRL_PLLn_CLK_SELECT_HSE0div1, pll_Q, pll_N);  //  PLLn, SRC, Q, N
	while(CLKCTRL_CPU_PLLstatus(0) != SUCCESS){};
	
	CLKCTRL_MAX_CLKSelection(CLKCTRL_MAX_CLK_PLL0);
    
  BRD_CPU_CLK = HSE0_Value * (pll_N + 2)/ (pll_Q + 1);
}

void BRD_Clock_Init_HSE0_60MHz(void)
{
  BRD_Clock_Init_HSE0_PLL(0, 4);
}  

void BRD_Clock_Init_HSE_PLL(uint32_t PLL_Mul)
{
  BRD_Clock_Init_HSE0_PLL(0, PLL_Mul - 2);
}
