#include "brdClock.h"
#include "brdLED.h"
#include "brdADC.h"
#include "brdDMA.h"
#include "brdUtils.h"

#include "brdDMA_SelectADC.h"

ADCx_InitTypeDef ADCxInitStruct;

#define ADC_CHANNEL       0
#define ADC_CHANNEL_DMA   5
#define ADC_FIFO_EN       FIEN5

#define DMA_CHANNEL      0
#define DMA_ADC1_SREQ    60

#define DATA_COUNT  6
uint32_t data_dma[DATA_COUNT];
uint32_t data_rd[DATA_COUNT];
uint32_t dmaCtrlStart;
uint32_t completedIRQ;

#define LED_OK            BRD_LED_1
#define LED_FAULT         BRD_LED_2
#define DELAY_LED_PERIOD  1000000

void FillData(uint32_t value);

ADCxControl logADC1_start, logADC1_IRQ;
DMAControl  logDMA_start, logDMA_IRQ;


int main(void)
{ 
  uint32_t i;
  volatile uint32_t dmaCtrl;
  
  // Clock
  BRD_Clock_Init_HSE_PLL(5);
  //  LED
  BRD_LEDs_Init();
    
  //  DMA
  BRD_DMA_Init();
  MDR_DMA->CHNL_REQ_MASK_SET = 0xFFFFFFFF; 
  MDR_DMA->CHNL_ENABLE_SET = 0xFFFFFFFF;
  
  //  DMA копирует значения каналов АЦП с 0-го по 5-й, по запросу от 5-го канала АЦП.
  //  Запрос к DMA снимется только при считывании RESULTCH_xx[5]
  DMA_DataCtrl_Pri.DMA_SourceBaseAddr = (uint32_t)&ADC1->RESULTCH_xx[ADC_CHANNEL];
  DMA_DataCtrl_Pri.DMA_DestBaseAddr   = (uint32_t)&data_dma;
  DMA_DataCtrl_Pri.DMA_CycleSize      = DATA_COUNT;
  BRD_DMA_Init_Channel (DMA_CHANNEL, &DMA_ChanCtrl);
  //  Assign ADC1_SREQ to DMA channel_0
  MDR_DMA->CHMUX0 = DMA_ADC1_SREQ;
  //  for restart
  dmaCtrlStart = BRD_DMA_Read_ChannelCtrl(DMA_CHANNEL);
    
  //  ADC
  BRD_ADCx_InitStruct(&ADCxInitStruct);
  ADCxInitStruct.ADC_FIFOEN_0_31 = ADC_FIFO_EN;
  ADCxInitStruct.ADC_PAUSE = 0x3F;
 
  ADCxInitStruct.ADC_WORKMODE   = 2;   // Cyclic
	ADCxInitStruct.ADC_SELMODE    = 1;   // Channel's switching On  
 
 // Запуск непрерывных измерений АЦП, измеряется 1-й канал.
  BRD_ADC1_Init(&ADCxInitStruct);

  //  АЦП формирует запрос SREQ0 к DMA по окончанию преобразования в 5-м канале
  ADC1->DMAREQ = (1 << 24) | ADC_CHANNEL_DMA;

  while (1)
  {
    // Запись массива значениями по умолчанию.
    FillData(7);
    completedIRQ = 0;
    
    // Запуск измерений 6-ти каналов.
    ADCx_SetChannels0(ADC1, 0x3F);
    
    //  Ожидание цикла ДМА
    while(!completedIRQ);

    // Отображение на светодиоды
    BRD_LED_Switch(LED_OK);
    Delay(DELAY_LED_PERIOD);
  }
}

void DMA_DONE0_Handler(void)
{ 
  //  Пусть непрерывно измеряется первый канал, который не дает запроса к DMA
  //  Если прописать 0, то будет измеряться текущий канал на момент выключения, 
  //  а это может оказаться 5-й канал, который дает запрос к DMA -> может зациклиться прерывание.
  ADCx_SetChannels0(ADC1, 0x1);

  // Стираем активнй запрос от 5-го канала АЦП  
  ADC1->RESULTCH_xx[ADC_CHANNEL];
  
  // Новый цикл DMA
  //if (BRD_DMA_Read_ChannelCtrl(DMA_CHANNEL) != dmaCtrlStart)
  BRD_DMA_Write_ChannelCtrl(DMA_CHANNEL, dmaCtrlStart);
  DMA_Cmd(DMA_CHANNEL, ENABLE);
  
  completedIRQ = 1;
  
  NVIC_ClearPendingIRQ (DMA_IRQn);
}

//void INT_ADC1_Handler(void)
//{
//  uint32_t i = 0;
//  volatile uint32_t cnt = 0;
//  while (ADC1->STATUS & 1)
//  { 
//    if (i < DATA_COUNT)
//      data_rd[i] = ADC1->RESULT;
//    ++cnt;
//  }  
//  
//  completedIRQ = 1;
//  
//  NVIC_ClearPendingIRQ (ADC1_IRQn);
//}  

void FillData(uint32_t value)
{
  uint32_t i;
  for (i = 0; i < DATA_COUNT; ++i)
  {
    data_dma[i] = value;
    data_rd[i] = value;
  }
}


