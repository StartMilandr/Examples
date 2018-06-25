#include "brdBtn.h"
	
// Инициализация линий ввода-вывода для работы с кнопками
void BRD_BTNs_Init (void)
{
  // Структура для инициализация линий ввода-вывода
  PORT_InitTypeDef GPIOInitStruct;

  // Включение тактирования портов
#ifndef USE_MDR1986VE3  
  RST_CLK_PCLKcmd (BRD_BTNs_PORT_CLK, ENABLE);
#else
  RST_CLK_PCLK2cmd (BRD_BTNs_PORT_CLK, ENABLE);
#endif  

  // Конфигурация линий ввода-вывода
  PORT_StructInit (&GPIOInitStruct);
  GPIOInitStruct.PORT_Pin       = BRD_BTNs_PIN_MASK;    // Конфигурируемые линии ввода-вывода
  GPIOInitStruct.PORT_SPEED     = PORT_SPEED_SLOW;     // Скорость передачи данных
  GPIOInitStruct.PORT_MODE      = PORT_MODE_DIGITAL;   // Режим работы линий
	
  // Инициализация линий ввода-вывода для работы со светодиодами
  PORT_Init (BRD_BTNs_PORT_MASK, &GPIOInitStruct);
	
#ifdef BRD_BTNS_DO_INIT_ext1
  GPIOInitStruct.PORT_Pin       = BRD_BTNs_PIN_MASK_ext1;
  PORT_Init (BRD_BTNs_PORT_MASK_ext1, &GPIOInitStruct);	
#endif
	
#ifdef BRD_BTNS_DO_INIT_ext2
  GPIOInitStruct.PORT_Pin       = BRD_BTNs_PIN_MASK_ext2;
  PORT_Init (BRD_BTNs_PORT_MASK_ext2, &GPIOInitStruct);	
#endif
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

#ifdef BRD_BTN_PIN_DOWN
uint32_t BRD_Is_BntAct_Down (void)
{
	return PORT_READ_PIN(BRD_BTN_PORT_DOWN, BRD_BTN_PIN_DOWN);
}
#endif

#ifdef BRD_BTN_PIN_LEFT
uint32_t BRD_Is_BntAct_Left (void)
{
	return PORT_READ_PIN(BRD_BTN_PORT_LEFT, BRD_BTN_PIN_LEFT);
}
#endif

#ifdef BRD_BTN_PIN_RIGHT
uint32_t BRD_Is_BntAct_Right (void)
{
	return PORT_READ_PIN(BRD_BTN_PORT_RIGHT, BRD_BTN_PIN_RIGHT);
}
#endif

#ifdef BRD_BTN_PIN_BACK
uint32_t BRD_Is_BntAct_Back (void)
{
	return PORT_READ_PIN(BRD_BTN_PORT_BACK, BRD_BTN_PIN_BACK);
}
#endif

