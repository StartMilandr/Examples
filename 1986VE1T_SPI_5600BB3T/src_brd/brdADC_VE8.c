#include "brdADC.h"

void BRD_ADC_PortInit(uint32_t Port_ClockMask, MDR_PORT_TypeDef* PORTx, uint32_t Port_PinsSel)
{
  PORT_InitTypeDef GPIOInitStruct;	
  
  //	Clock for PORTC
  CLKCTRL_PER0_CLKcmd(Port_ClockMask, ENABLE);
  PORTx->KEY = _KEY_;
  
  //  Post apply config
  PORT_StructInit(&GPIOInitStruct);
  
  GPIOInitStruct.PORT_Pin     = Port_PinsSel;
  GPIOInitStruct.PORT_SOE     = PORT_SOE_IN;
  GPIOInitStruct.PORT_SANALOG = PORT_SANALOG_ANALOG;
  
  PORT_Init(PORTx, &GPIOInitStruct);
}

void BRD_ADCx_LogReg(ADCxControl* ADCx, ADCxControl* logRegs)
{
  logRegs->CONFIG0 = ADCx->CONFIG0;
  logRegs->CONFIG1 = ADCx->CONFIG1;
  logRegs->CONFIG2 = ADCx->CONFIG2;
  logRegs->CONTROL = ADCx->CONTROL;
  logRegs->STATUS  = ADCx->STATUS;
  logRegs->RESULT  = ADCx->RESULT;
  
  //logRegs->RESULTCH_xx[64] = ADC1->RESULTCH_xx[64]
  
  logRegs->MAX_LEVEL = ADCx->MAX_LEVEL;
  logRegs->MIN_LEVEL = ADCx->MIN_LEVEL;
  logRegs->CHSEL0    = ADCx->CHSEL0;
  logRegs->CHSEL1    = ADCx->CHSEL1;
  logRegs->DMAREQ    = ADCx->DMAREQ;
  logRegs->STATRCH0  = ADCx->STATRCH0;
  logRegs->STATRCH1  = ADCx->STATRCH1;
  
  logRegs->FIFOEN0 = ADCx->FIFOEN0;
  logRegs->FIFOEN1 = ADCx->FIFOEN1;  
}  

//void BRD_ADCs_InitStruct(ADC_InitTypeDef  *ADCInitStruct)
//{
//  // Общая конфигурация АЦП
//  ADC_StructInit (ADCInitStruct);
//	  
//  ADCInitStruct->ADC_StartDelay           = 0;                                   // Задержка запуска модулей АЦП
//  ADCInitStruct->ADC_TempSensor           = ADC_TEMP_SENSOR_Disable;             // Температурный датчик
//  ADCInitStruct->ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Disable;   // Усилитель температурного датчика
//  ADCInitStruct->ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Disable;  // Преобразование для канала температурного датчика
//  ADCInitStruct->ADC_IntVRefConversion    = ADC_VREF_CONVERSION_Disable;         // Преобразование для канала внутренного источника опорного напряжения
//  ADCInitStruct->ADC_IntVRefTrimming      = 0;                                   // Подстройка опорного напряжения
//}  

//void BRD_ADCs_Init(ADC_InitTypeDef  *ADCInitStruct)
//{
//  // Clock ACD
//  RST_CLK_PCLKcmd (RST_CLK_PCLK_ADC, ENABLE);

//  // Init ADC 
//  ADC_DeInit();
//  ADC_Init(ADCInitStruct);
//}  

void BRD_ADCx_InitStruct(ADCx_InitTypeDef *ADCxInitStruct)
{
  ADC_StructInit(ADCxInitStruct);
	ADCxInitStruct->ADC_RH_MODE = ADCx_CONFIG0_RH_MODE_ADC_POW;
	ADCxInitStruct->ADC_SETUP = 5;
	ADCxInitStruct->ADC_PAUSE = 5;
}  

void BRD_ADC1_Init(ADCx_InitTypeDef *ADCxInitStruct)
{
  CLKCTRL_PER1_CLKcmd(CLKCTRL_PER1_CLK_MDR_ADC1_EN, ENABLE);    
	ADCx_CLK_en(ADC1, ADCx_CLKSRC_MAX_CLK, ADCx_CLKdiv1);			
	ADC1->KEY = 0x8555AAA1;
  
  
	ADC_Init(ADC1, ADCxInitStruct);
	ADCx_Cmd(ADC1, ENABLE);
}

uint16_t BRD_ADC1_GetValue(void)
{	 
	ADCx_Start(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_NE)==RESET){}
  
  return ADCx_GetResult(ADC1);    	
}

void BRD_ADC1_StartAndWaitCompleted(void)
{	 
	ADCx_Start(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_NE)==RESET){}
}


//void BRD_ADC1_InitIRQ(uint32_t ADC_IT)
//{
//  ADC1_ITConfig (ADC_IT, ENABLE);

//  NVIC_SetPriority(ADC_IRQn, 1);
//  NVIC_EnableIRQ(ADC_IRQn); 
//}

//void BRD_ADC1_InitIRQ_EndConv(void)
//{
//  // Включение прерываний по окончании аналого-цифрового преобразования
//  BRD_ADC1_InitIRQ(ADC1_IT_END_OF_CONVERSION);
//}  

//void ADC_IRQHandler (void)
//{
//  // Если возникло прерывание по завершению преобразования
//  if (ADC1_GetITStatus (ADC1_IT_END_OF_CONVERSION))
//  {
//    // Получение результата преобразования для сброса флага прерывания
//    digit = ADC1_GetResult() & 0xFFF;
//  }
//}

