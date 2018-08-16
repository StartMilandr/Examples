#ifndef _BRD_UART_H
#define _BRD_UART_H

#include <stdint.h>
#include <MDR32F9Qx_uart.h>

#include "brdPort.h"

typedef struct {
  //  Pins
  brdPort_Obj*      PortTX_Obj;
  brdPort_Obj*      PortRX_Obj;
  
  //  Uart Init
  MDR_UART_TypeDef* UARTx;
  uint32_t          ClockMask;
  
  //  Uart Settings
  UART_InitTypeDef* pInitStruct;
  uint32_t          BRG_HCLK_div;
  IRQn_Type         Uart_IRQn;
} BrdUART_Obj;

void BRD_UART_PortStructInitDef(PORT_InitTypeDef* InitStruct);
void BRD_UART_PortInit(BrdUART_Obj* BRD_Uart);
void BRD_UART_Init(BrdUART_Obj* BRD_Uart, uint32_t BaudRate);
void BRD_UART_InitIRQ(BrdUART_Obj* BRD_Uart, uint32_t IQR_Mask, uint32_t priority);

void BRD_Uart_SetBaud(BrdUART_Obj* BRD_Uart, uint32_t baudRate, uint32_t freqCPU);



#endif //_BRD_UART_H
