#ifndef _BRD_ADC_H
#define _BRD_ADC_H

#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_dac.h>

#include "brdDef.h"

#define VOLT_TO_DAC(volt) ((0xFFF) / (3.3) * (volt))

#define BRD_DAC1_PortInit()  BRD_DAC_PortInit(BRD_DAC1_CLOCK, BRD_DAC1_PORT, BRD_DAC1_PIN)
#define BRD_DAC2_PortInit()  BRD_DAC_PortInit(BRD_DAC2_CLOCK, BRD_DAC2_PORT, BRD_DAC2_PIN)

#define BRD_DAC1_SetEnable(enable)  DAC1_Cmd(enable)
#define BRD_DAC2_SetEnable(enable)  DAC2_Cmd(enable)

void BRD_DACs_Init(void);

void BRD_DAC_PortInit(uint32_t Port_ClockMask, MDR_PORT_TypeDef* PORTx, uint32_t Port_PinsSel);


#endif //_BRD_ADC_H
