#ifndef _BRD_PORT_H
#define _BRD_PORT_H

#include <stdint.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>

typedef struct {
  MDR_PORT_TypeDef* PORTx;
  uint32_t          Port_ClockMask; 
  uint32_t          Port_PinsSel;
  PORT_FUNC_TypeDef Port_PinsFunc;
  uint32_t          Port_PinsFunc_ClearMask;
  //  Default settings
  PORT_InitTypeDef* pInitStruct;
}  brdPort_Obj;  


void BRD_Port_Init (brdPort_Obj* BRD_Port);

#endif //_BRD_PORT_H
