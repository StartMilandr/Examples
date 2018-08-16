#include "brdLed.h"

void BRD_LEDs_Init(void)
{	
	PORT_InitTypeDef GPIOInitStruct;	
	
	//	Clock for PORTC
	RST_CLK_PCLKcmd (BRD_LED_PORT_CLK, ENABLE);
	
	//  Post apply config
	PORT_StructInit(&GPIOInitStruct);
  GPIOInitStruct.PORT_Pin        = BRD_LED_Pins;
  GPIOInitStruct.PORT_OE         = PORT_OE_OUT;
  GPIOInitStruct.PORT_SPEED      = PORT_SPEED_SLOW;
  GPIOInitStruct.PORT_MODE       = PORT_MODE_DIGITAL;
	
	PORT_Init(BRD_LED_PORT, &GPIOInitStruct);
}

void BRD_LEDs_InitEx(uint32_t pinSelect)
{	
	PORT_InitTypeDef GPIOInitStruct;	
	
	//	Clock for PORTC
	RST_CLK_PCLKcmd (BRD_LED_PORT_CLK, ENABLE);
	
	//  Post apply config
	PORT_StructInit(&GPIOInitStruct);
  GPIOInitStruct.PORT_Pin        = pinSelect;
  GPIOInitStruct.PORT_OE         = PORT_OE_OUT;
  GPIOInitStruct.PORT_SPEED      = PORT_SPEED_SLOW;
  GPIOInitStruct.PORT_MODE       = PORT_MODE_DIGITAL;
	
	PORT_Init(BRD_LED_PORT, &GPIOInitStruct);
}

void BRD_LED_Set(uint32_t LEDs_Sel, uint32_t isOn)
{
	if (isOn)
		PORT_SetBits(BRD_LED_PORT, LEDs_Sel);
	else
		PORT_ResetBits(BRD_LED_PORT, LEDs_Sel);
}

void BRD_LED_Switch(uint32_t LEDs_Sel)
{
#ifndef BRD_LED_JTAG_PROT_CLR  
	BRD_LED_PORT->RXTX ^= LEDs_Sel;
#else
  uint32_t reg = BRD_LED_PORT->RXTX;
  BRD_LED_PORT->RXTX = (reg ^ LEDs_Sel) & BRD_LED_JTAG_PROT_CLR;
#endif
}	

uint32_t BRD_LED_Get(uint32_t LEDs_Sel)
{
  return (BRD_LED_PORT->RXTX & LEDs_Sel) == LEDs_Sel;
}

