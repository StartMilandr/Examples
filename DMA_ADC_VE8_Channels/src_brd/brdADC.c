#include "brdADC.h"


void BRD_ADC_PortInit(uint32_t Port_ClockMask, MDR_PORT_TypeDef* PORTx, uint32_t Port_PinsSel)
{
  // Rec
  PORT_InitTypeDef GPIOInitStruct;

  // Clock
  RST_CLK_PCLKcmd (Port_ClockMask, ENABLE);

  // ������������ ����� �����-������
  PORT_StructInit (&GPIOInitStruct);
  GPIOInitStruct.PORT_Pin  = Port_PinsSel;
  GPIOInitStruct.PORT_OE   = PORT_OE_IN;
  GPIOInitStruct.PORT_MODE = PORT_MODE_ANALOG;

  // ������������� ����� D
  PORT_Init (PORTx, &GPIOInitStruct);
}

void BRD_ADCs_InitStruct(ADC_InitTypeDef  *ADCInitStruct)
{
  // ����� ������������ ���
  ADC_StructInit (ADCInitStruct);
  ADCInitStruct->ADC_StartDelay           = 0;                                   // �������� ������� ������� ���
  ADCInitStruct->ADC_TempSensor           = ADC_TEMP_SENSOR_Disable;             // ������������� ������
  ADCInitStruct->ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Disable;   // ��������� �������������� �������
  ADCInitStruct->ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Disable;  // �������������� ��� ������ �������������� �������
  ADCInitStruct->ADC_IntVRefConversion    = ADC_VREF_CONVERSION_Disable;         // �������������� ��� ������ ����������� ��������� �������� ����������
  ADCInitStruct->ADC_IntVRefTrimming      = 0;                                   // ���������� �������� ����������
}  

void BRD_ADCs_Init(ADC_InitTypeDef  *ADCInitStruct)
{
  // Clock ACD
  RST_CLK_PCLKcmd (RST_CLK_PCLK_ADC, ENABLE);

  // Init ADC 
  ADC_DeInit();
  ADC_Init(ADCInitStruct);
}  

void BRD_ADCx_InitStruct(ADCx_InitTypeDef *ADCxInitStruct)
{
  // ������������ ������ ADC1
  ADCx_StructInit (ADCxInitStruct);
  ADCxInitStruct->ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;           // �������� ������������ ������ ���
  ADCxInitStruct->ADC_SamplingMode     = ADC_SAMPLING_MODE_SINGLE_CONV;  // ����� ��������������
  ADCxInitStruct->ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;       // ����� ��������������� ������������ �������
  ADCxInitStruct->ADC_ChannelNumber    = ADC_CH_ADC7;                    // ����� ���
  ADCxInitStruct->ADC_Channels         = 0;                              // ������ ��� ��� ������ ��������������� ������������ �������
  ADCxInitStruct->ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;      // �������� ������ �������� ����������
  ADCxInitStruct->ADC_LowLevel         = 0;                              // ������ ������� �������� ����������
  ADCxInitStruct->ADC_HighLevel        = 0;                              // ������� ������� �������� ����������
  ADCxInitStruct->ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;       // �������� �������� ����������
  ADCxInitStruct->ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;    // ����� ����������� ��������� �������� ����������
  ADCxInitStruct->ADC_Prescaler        = ADC_CLK_div_512;                // ������������ ������� ������������ ������ ���
  ADCxInitStruct->ADC_DelayGo          = 7;                              // �������� ����� �������� ��� ����� ������ ������
}  

void BRD_ADC1_Init(ADCx_InitTypeDef *ADCxInitStruct)
{
  ADC1_Init(ADCxInitStruct);
  ADC1_Cmd(ENABLE);
}

void BRD_ADC1_InitIRQ(uint32_t ADC_IT)
{
  ADC1_ITConfig (ADC_IT, ENABLE);

  NVIC_SetPriority(ADC_IRQn, 1);
  NVIC_EnableIRQ(ADC_IRQn); 
}

void BRD_ADC1_InitIRQ_EndConv(void)
{
  // ��������� ���������� �� ��������� �������-��������� ��������������
  BRD_ADC1_InitIRQ(ADC1_IT_END_OF_CONVERSION);
}  

//void ADC_IRQHandler (void)
//{
//  // ���� �������� ���������� �� ���������� ��������������
//  if (ADC1_GetITStatus (ADC1_IT_END_OF_CONVERSION))
//  {
//    // ��������� ���������� �������������� ��� ������ ����� ����������
//    digit = ADC1_GetResult() & 0xFFF;
//  }
//}

