#include "brdClock.h"


uint32_t BRD_CPU_CLK = (uint32_t)8000000;

// -------------------------- USE_MDR1986VE1x ---------------------	
#ifdef USE_MDR1986VE1T

typedef enum {
	RI_till_10KHz, RI_till_200KHz, RI_till_500KHz, RI_till_1MHz, 
  RI_Gens_Off, 
  RI_till_40MHz, RI_till_80MHz, RI_over_80MHz
} SelectRI;

void SetSelectRI(SelectRI extraI)
{
	uint32_t temp;
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_BKP, ENABLE);

	temp = MDR_BKP->REG_0E & 0xFFFFFFC0; 
	temp |= (extraI << 3) | extraI;
	MDR_BKP->REG_0E = temp;		
}

void BRD_Clock_Init_HSE_PLL(uint32_t PLL_Mul_sub1)
{
  uint32_t freqCPU;
  
	RST_CLK_DeInit();
	
	/* Enable HSE (High Speed External) clock */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	while (RST_CLK_HSEstatus() != SUCCESS);

//	/* Configures the CPU_PLL clock source */
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, PLL_Mul_sub1);

	/* Enables the CPU_PLL */
	RST_CLK_CPU_PLLcmd(ENABLE);
	while (RST_CLK_CPU_PLLstatus() == ERROR);		
	
	/* Enables the RST_CLK_PCLK_EEPROM */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);

	/* Sets the code latency value */
  freqCPU = HSE_Value * (PLL_Mul_sub1 + 1);
	if (freqCPU < 25E+6)
		EEPROM_SetLatency(EEPROM_Latency_0);
	else if (freqCPU < 50E+6)
		EEPROM_SetLatency(EEPROM_Latency_1);
	else if (freqCPU < 75E+6)
		EEPROM_SetLatency(EEPROM_Latency_2);
	else if (freqCPU < 100E+6)
		EEPROM_SetLatency(EEPROM_Latency_3);
	else if (freqCPU < 125E+6)
		EEPROM_SetLatency(EEPROM_Latency_4);
	else //if (PLL_Mul * HSE_Value <= 150E+6)
		EEPROM_SetLatency(EEPROM_Latency_5);

	//	Additional Supply Power
	if (freqCPU < 40E+6)
		SetSelectRI(RI_till_40MHz);
	else if (freqCPU < 80E+6)
		SetSelectRI(RI_till_80MHz);
	else 
		SetSelectRI(RI_over_80MHz);	
		
	/* Select the CPU_PLL output as input for CPU_C3_SEL */
	RST_CLK_CPU_PLLuse(ENABLE);
	/* Set CPUClk Prescaler */
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
  
  //  Update System Clock
  BRD_CPU_CLK = freqCPU;  
}

void BRD_Clock_Init_HSE_dir(void)  
{
	RST_CLK_DeInit();
	
	/* Enable HSE (High Speed External) clock */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	while (RST_CLK_HSEstatus() != SUCCESS);

	//	Additional Supply Power
	SetSelectRI(RI_till_40MHz);

	RST_CLK_CPU_PLLuse(DISABLE);
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
  
  //  Update System Clock
  BRD_CPU_CLK = HSE_Value;    
}


// -------------------------- USE_MDR1986VE9x ---------------------	
#elif defined ( USE_MDR1986VE9x ) || defined ( USE_MDR1986BE4 ) || defined ( USE_MDR1901VC1T )

void BRD_Clock_Init_HSE_PLL(uint32_t PLL_Mul_sub1)  // 128 MHz
{
  // Сброс настроек системы тактирования
  RST_CLK_DeInit();

  // Инициализация генератора на внешнем кварцевом резонаторе (HSE)
  RST_CLK_HSEconfig (RST_CLK_HSE_ON);
  while (RST_CLK_HSEstatus() != SUCCESS);

  // Инициализация блока PLL
  // Включение использования PLL
  RST_CLK_CPU_PLLcmd (ENABLE);

  // Настройка источника и коэффициента умножения PLL
  // (CPU_C1_SEL = HSE)
  RST_CLK_CPU_PLLconfig (RST_CLK_CPU_PLLsrcHSEdiv1, PLL_Mul_sub1);
  while (RST_CLK_CPU_PLLstatus() != SUCCESS);

  // Подключение PLL к системе тактирования
  // (CPU_C2_SEL = PLLCPUo)
  RST_CLK_CPU_PLLuse (ENABLE);

  // Настройка коэффициента деления блока CPU_C3_SEL
  // (CPU_C3_SEL = CPU_C2)
  RST_CLK_CPUclkPrescaler (RST_CLK_CPUclkDIV1);

  // Использование процессором сигнала CPU_C3
  // (HCLK = CPU_C3)
  RST_CLK_CPUclkSelection (RST_CLK_CPUclkCPU_C3);
  
  //  Update System Clock
  BRD_CPU_CLK = HSE_Value * (PLL_Mul_sub1 + 1);
}

void BRD_Clock_Init_HSE_dir(void)  
{
	RST_CLK_DeInit();
	
	/* Enable HSE (High Speed External) clock */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	while (RST_CLK_HSEstatus() != SUCCESS);

	RST_CLK_CPU_PLLuse(DISABLE);
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
  
  //  Update System Clock
  BRD_CPU_CLK = HSE_Value;  
}

// -------------------------- USE_MDR1986VE3 ---------------------
#elif defined ( USE_MDR1986VE3 ) 

void BRD_Clock_Init_HSE_PLL(uint32_t PLL_Mul_sub1)  // 128 MHz
{
	RST_CLK_DeInit();
	
	/* Enable HSE (High Speed External) clock */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	while (RST_CLK_HSEstatus() != SUCCESS);

//	/* Configures the CPU_PLL clock source */
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, PLL_Mul_sub1);

	/* Enables the CPU_PLL */
	RST_CLK_CPU_PLLcmd(ENABLE);
	while (RST_CLK_CPU_PLLstatus() == ERROR);		
	
	/* Enables the RST_CLK_PCLK_EEPROM */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);

		/* Sets the code latency value */
	if (PLL_Mul * HSE_Value < 25E+6)
		EEPROM_SetLatency(EEPROM_Latency_0);
	else if (PLL_Mul * HSE_Value < 50E+6)
		EEPROM_SetLatency(EEPROM_Latency_1);
	else if (PLL_Mul * HSE_Value < 75E+6)
		EEPROM_SetLatency(EEPROM_Latency_2);
	else if (PLL_Mul * HSE_Value < 100E+6)
		EEPROM_SetLatency(EEPROM_Latency_3);
	else if (PLL_Mul * HSE_Value < 125E+6)
		EEPROM_SetLatency(EEPROM_Latency_4);
	else //if (PLL_Mul * HSE_Value <= 150E+6)
		EEPROM_SetLatency(EEPROM_Latency_5);
		
	/* Select the CPU_PLL output as input for CPU_C3_SEL */
	RST_CLK_CPU_PLLuse(ENABLE);
	/* Set CPUClk Prescaler */
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
  
  //  Update System Clock
  BRD_CPU_CLK = HSE_Value * (PLL_Mul_sub1 + 1);    
}


#endif



