#ifndef _BRD_LED__H
#define _BRD_LED__H

#include <stdint.h>
#include "brdDef.h"

//  Led Pin Definitions
#ifdef USE_BOARD_VE_8 
  #include  <mdr32f8_port.h>
#else  
  #include  <MDR32F9Qx_port.h>
  #include <MDR32F9Qx_rst_clk.h>  
#endif

void BRD_LEDs_Init(void);
void BRD_LED_Switch(uint32_t LEDs_Sel);
void BRD_LED_Set(uint32_t LEDs_Sel, uint32_t isOn);
uint32_t BRD_LED_Get(uint32_t LEDs_Sel);

void BRD_LEDs_InitEx(uint32_t pinSelect);
  
#endif //_BRD_LED__H
