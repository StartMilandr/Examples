#include "brdDAC.h"

void BRD_DAC_PortInit(uint32_t Port_ClockMask, MDR_PORT_TypeDef* PORTx, uint32_t Port_PinsSel)
{
  // Rec
  PORT_InitTypeDef GPIOInitStruct;

  // Clock
  RST_CLK_PCLKcmd (Port_ClockMask, ENABLE);

  // Конфигурация линий ввода-вывода
  PORT_StructInit (&GPIOInitStruct);
  GPIOInitStruct.PORT_Pin  = Port_PinsSel;
  GPIOInitStruct.PORT_MODE = PORT_MODE_ANALOG;

  // Инициализация порта
  PORT_Init (PORTx, &GPIOInitStruct);  
}

void BRD_DACs_Init(void)
{
  RST_CLK_PCLKcmd (RST_CLK_PCLK_DAC, ENABLE);  
  
  // Деинициализация ЦАП
  DAC_DeInit();

  DAC_Init(DAC_SYNC_MODE_Independent, DAC1_AVCC, DAC2_AVCC);
}

