#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_uart.h>

#include "brdUart.h"

void BRD_UART_PortStructInitDef(PORT_InitTypeDef* InitStruct)
{
  InitStruct->PORT_PULL_UP   = PORT_PULL_UP_OFF;
  InitStruct->PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
  InitStruct->PORT_PD_SHM    = PORT_PD_SHM_OFF;
  InitStruct->PORT_PD        = PORT_PD_DRIVER;
  InitStruct->PORT_GFEN      = PORT_GFEN_OFF;
  InitStruct->PORT_SPEED     = PORT_SPEED_MAXFAST;
  InitStruct->PORT_MODE      = PORT_MODE_DIGITAL;
}  

// ������������ ����� �����-������
void BRD_UART_PortInit (BrdUART_Obj* BRD_Uart)
{
  BRD_Port_Init(BRD_Uart->PortTX_Obj);
  BRD_Port_Init(BRD_Uart->PortRX_Obj);
}  

//  ������������� ������ UART
void BRD_UART_Init (BrdUART_Obj* BRD_Uart, uint32_t BaudRate)
{
  // ���������� ������������ ����� F � ������ UART
  RST_CLK_PCLKcmd (BRD_Uart->ClockMask, ENABLE);

  // ������������� ������ UART
  BRD_Uart->pInitStruct->UART_BaudRate = BaudRate;
  UART_Init (BRD_Uart->UARTx, BRD_Uart->pInitStruct);

  // ����� ������������ �������� ������� ������ UART
  UART_BRGInit (BRD_Uart->UARTx, BRD_Uart->BRG_HCLK_div);

//  // ����� ���������� ���������� (����� � �������� ������)
//  if (BRD_Uart->IQR_Mask)
//    UART_ITConfig (BRD_Uart->UARTx, BRD_Uart->IQR_Mask, ENABLE);

  // ���������� ������ ������ UART
  UART_Cmd (BRD_Uart->UARTx, ENABLE);
}

void BRD_UART_InitIRQ(BrdUART_Obj* BRD_Uart, uint32_t IQR_Mask, uint32_t priority)
{
  // ����� ���������� ���������� (����� � �������� ������)
  UART_ITConfig (BRD_Uart->UARTx, IQR_Mask, ENABLE);
  
  // ���������� ���������� ����������� ���������� �� UART
  NVIC_SetPriority (BRD_Uart->Uart_IRQn, priority);

  // ���������� ���������� ���������� �� UART
  NVIC_EnableIRQ (BRD_Uart->Uart_IRQn);
}	


void BRD_Uart_SetBaud(BrdUART_Obj* BRD_Uart, uint32_t baudRate, uint32_t freqCPU)
{
	uint32_t divider = freqCPU / (baudRate >> 2);
	uint32_t CR_tmp = BRD_Uart->UARTx->CR;
	uint32_t LCR_tmp = BRD_Uart->UARTx->LCR_H;
	
//  while ( !(BRD_Uart->UARTx->FR & UART_FLAG_TXFE) ); // wait FIFO empty
	while ( (BRD_Uart->UARTx->FR & UART_FLAG_BUSY) ); // wait 

  BRD_Uart->UARTx->CR = 0;
  BRD_Uart->UARTx->IBRD = divider >> 6;
  BRD_Uart->UARTx->FBRD = divider & 0x003F;
  BRD_Uart->UARTx->LCR_H = LCR_tmp;
  BRD_Uart->UARTx->CR = CR_tmp;
}

//// ��������� ���������� ���������� ������ UART
//void UARTx_IRQHandler (void)
//{
//  // ���� ��������� ���������� �� ���������� ������ ������...
//  if (UART_GetITStatusMasked (UART_X, UART_IT_RX) == SET)
//  {
//    // ����� ����������
//    UART_ClearITPendingBit (UART_X, UART_IT_RX);

//    // ������ ���-�� �����

//  }

//  // ���� ��������� ���������� �� ���������� �������� ������...
//  if (UART_GetITStatusMasked(UART_X, UART_IT_TX) == SET)
//  {
//    // ����� ����������
//    UART_ClearITPendingBit (UART_X, UART_IT_TX);

//    // �������� �����

//  }
//}
