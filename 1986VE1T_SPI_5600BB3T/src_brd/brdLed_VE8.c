#include <mdr32f8_port.h>
#include <mdr32f8_clkctrl.h>

#include "brdDef.h"

void BRD_LEDs_Init(void)
{	
	PORT_InitTypeDef GPIOInitStruct;	
	
	//	Clock for PORTC
	CLKCTRL_PER0_CLKcmd(BRD_LED_PORT_CLK, ENABLE);
	BRD_LED_PORT->KEY = _KEY_;
  
	//  Post apply config
	PORT_StructInit(&GPIOInitStruct);
  
  GPIOInitStruct.PORT_Pin     = BRD_LED_Pins;
  GPIOInitStruct.PORT_SOE     = PORT_SOE_OUT;
  GPIOInitStruct.PORT_SANALOG = PORT_SANALOG_DIGITAL;
	GPIOInitStruct.PORT_SPD     = PORT_SPD_OFF;
	GPIOInitStruct.PORT_SPWR    = PORT_SPWR_10;
	
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
	BRD_LED_PORT->RXTX ^= LEDs_Sel;
}	


