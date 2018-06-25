#ifndef _BRD_ADC_H
#define _BRD_ADC_H

#include "brdDef.h"

#ifndef USE_BOARD_VE_8
  #include <MDR32F9Qx_port.h>
  #include <MDR32F9Qx_rst_clk.h>
  #include <MDR32F9Qx_adc.h>
#else
  #include <mdr32f8_port.h>
  #include <mdr32f8_clkctrl.h>
  #include <mdr32f8_adc.h>
  
  #include "brdVE8_toVEx.h"
  
  void BRD_ADCx_LogReg(ADCxControl* ADCx, ADCxControl* logRegs);
#endif

//  General ADC Init
void BRD_ADC_PortInit(uint32_t Port_ClockMask, MDR_PORT_TypeDef* PORTx, uint32_t Port_PinsSel);
void BRD_ADCs_InitStruct(ADC_InitTypeDef  *ADCInitStruct);
void BRD_ADCs_Init(ADC_InitTypeDef  *ADCInitStruct);

//  Custom ADCx Init
void BRD_ADCx_InitStruct(ADCx_InitTypeDef *ADCxInitStruct);
void BRD_ADC1_Init(ADCx_InitTypeDef *ADCxInitStruct);
void BRD_ADC1_InitIRQ(uint32_t ADC_IT);
void BRD_ADC1_InitIRQ_EndConv(void);

uint16_t BRD_ADC1_GetValue(void);
void BRD_ADC1_StartAndWaitCompleted(void);

void BRD_ADC1_RunSingle(uint32_t goEna);
void BRD_ADC1_RunSample(uint32_t sampleEna);



#endif //_BRD_ADC_H
