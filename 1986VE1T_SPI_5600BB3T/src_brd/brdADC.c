#include "brdADC.h"


void BRD_ADC_PortInit(uint32_t Port_ClockMask, MDR_PORT_TypeDef* PORTx, uint32_t Port_PinsSel)
{
  // Rec
  PORT_InitTypeDef GPIOInitStruct;

  // Clock
  RST_CLK_PCLKcmd (Port_ClockMask, ENABLE);

  // Конфигурация линий ввода-вывода
  PORT_StructInit (&GPIOInitStruct);
  GPIOInitStruct.PORT_Pin  = Port_PinsSel;
  GPIOInitStruct.PORT_OE   = PORT_OE_IN;
  GPIOInitStruct.PORT_MODE = PORT_MODE_ANALOG;

  // Инициализация порта D
  PORT_Init (PORTx, &GPIOInitStruct);
}

void BRD_ADCs_InitStruct(ADC_InitTypeDef  *ADCInitStruct)
{
  // Общая конфигурация АЦП
  ADC_StructInit (ADCInitStruct);
  ADCInitStruct->ADC_StartDelay           = 0;                                   // Задержка запуска модулей АЦП
  ADCInitStruct->ADC_TempSensor           = ADC_TEMP_SENSOR_Disable;             // Температурный датчик
  ADCInitStruct->ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Disable;   // Усилитель температурного датчика
  ADCInitStruct->ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Disable;  // Преобразование для канала температурного датчика
  ADCInitStruct->ADC_IntVRefConversion    = ADC_VREF_CONVERSION_Disable;         // Преобразование для канала внутренного источника опорного напряжения
  ADCInitStruct->ADC_IntVRefTrimming      = 0;                                   // Подстройка опорного напряжения
}  

void BRD_ADCs_Init(ADC_InitTypeDef  *ADCInitStruct)
{
  // Clock ACD
  RST_CLK_PCLKcmd (RST_CLK_PCLK_ADC, ENABLE);

  // Init ADC 
  ADC_DeInit();
  ADC_Init(ADCInitStruct);
}  

void BRD_ADC1_RunSingle(uint32_t goEna)
{
  if (goEna)
    MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_GO;
  else
    MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_GO;
}

void BRD_ADC1_RunSample(uint32_t sampleEna)
{
  if (sampleEna)
    MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_SAMPLE;
  else
    MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_SAMPLE;
}


void BRD_ADCx_InitStruct(ADCx_InitTypeDef *ADCxInitStruct)
{
  // Конфигурация модуля ADC1
  ADCx_StructInit (ADCxInitStruct);
  ADCxInitStruct->ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;           // Источник тактирования модуля АЦП
  ADCxInitStruct->ADC_SamplingMode     = ADC_SAMPLING_MODE_SINGLE_CONV;  // Режим преобразования
  ADCxInitStruct->ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;       // Режим автоматического переключения каналов
  ADCxInitStruct->ADC_ChannelNumber    = ADC_CH_ADC7;                    // Канал АЦП
  ADCxInitStruct->ADC_Channels         = 0;                              // Каналы АЦП для режима автоматического переключения каналов
  ADCxInitStruct->ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;      // Контроль уровня входного напряжения
  ADCxInitStruct->ADC_LowLevel         = 0;                              // Нижний уровень входного напряжения
  ADCxInitStruct->ADC_HighLevel        = 0;                              // Верхний уровень входного напряжения
  ADCxInitStruct->ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;       // Источник опорного напряжения
  ADCxInitStruct->ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;    // Режим внутреннего источника опроного напряжения
  ADCxInitStruct->ADC_Prescaler        = ADC_CLK_div_512;                // Предделитель частоты тактирования модуля АЦП
  ADCxInitStruct->ADC_DelayGo          = 7;                              // Задержка перед запуском АЦП после выбора канала
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
  // Включение прерываний по окончании аналого-цифрового преобразования
  BRD_ADC1_InitIRQ(ADC1_IT_END_OF_CONVERSION);
}  

//void ADC_IRQHandler (void)
//{
//  // Если возникло прерывание по завершению преобразования
//  if (ADC1_GetITStatus (ADC1_IT_END_OF_CONVERSION))
//  {
//    // Получение результата преобразования для сброса флага прерывания
//    digit = ADC1_GetResult() & 0xFFF;
//  }
//}

