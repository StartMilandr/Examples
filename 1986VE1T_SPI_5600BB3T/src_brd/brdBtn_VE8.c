#include "brdBtn.h"


// Инициализация линий ввода-вывода для работы с кнопками
void BRD_BTNs_Init (void)
{
  // Структура для инициализация линий ввода-вывода
  PORT_InitTypeDef GPIOInitStruct;

  // Включение тактирования портов
  CLKCTRL_PER0_CLKcmd (BRD_BTNs_PORT_CLK, ENABLE);
	BRD_BTNs_PORT->KEY = _KEY_;

  // Конфигурация линий ввода-вывода
  PORT_StructInit (&GPIOInitStruct);
	
	GPIOInitStruct.PORT_Pin   = BRD_BTNs_PIN_MASK;
  GPIOInitStruct.PORT_SOE    = PORT_SOE_IN;
  GPIOInitStruct.PORT_SANALOG  = PORT_SANALOG_DIGITAL;
	GPIOInitStruct.PORT_SPD = PORT_SPD_OFF;
	GPIOInitStruct.PORT_SPWR = PORT_SPWR_10;
	// irq enable and set active irq level
	GPIOInitStruct.PORT_SIE = PORT_SIE_ON;
	GPIOInitStruct.PORT_SIT = PORT_SIT_LOW;  
  
  // Инициализация линий ввода-вывода для работы со светодиодами
  PORT_Init (BRD_BTNs_PORT, &GPIOInitStruct);
}
	
#ifndef BRD_BTNs_PUSH_TO_GND
  #define PORT_READ_PIN(port, pin) (PORT_ReadInputDataBit (port, pin))
#else
  #define PORT_READ_PIN(port, pin) (!(PORT_ReadInputDataBit (port, pin)))
#endif

uint32_t BRD_Is_BntAct_Select (void)
{
	return PORT_READ_PIN(BRD_BTN_PORT_SEL, BRD_BTN_PIN_SEL);
}

uint32_t BRD_Is_BntAct_Up (void)
{
	return PORT_READ_PIN(BRD_BTN_PORT_UP, BRD_BTN_PIN_UP);
}

uint32_t BRD_Is_BntAct_Down (void)
{
	return PORT_READ_PIN(BRD_BTN_PORT_DOWN, BRD_BTN_PIN_DOWN);
}

#ifdef BRD_BTN_PIN_LEFT
  uint32_t BRD_Is_BntAct_Left (void)
  {
    return PORT_READ_PIN(BRD_BTN_PORT_LEFT, BRD_BTN_PIN_LEFT);
  }
#else
  uint32_t BRD_Is_BntAct_Left (void)
  {
    return BRD_Is_BntAct_Select();
  }  
#endif

#ifdef BRD_BTN_PIN_RIGHT
  uint32_t BRD_Is_BntAct_Right (void)
  {
    return PORT_READ_PIN(BRD_BTN_PORT_RIGHT, BRD_BTN_PIN_RIGHT);
  }
#else
  uint32_t BRD_Is_BntAct_Right (void)
  {
    return BRD_Is_BntAct_Down();
  }
#endif

#ifdef BRD_BTN_PIN_BACK
uint32_t BRD_Is_BntAct_Back (void)
{
	return PORT_READ_PIN(BRD_BTN_PORT_BACK, BRD_BTN_PIN_BACK);
}
#endif

