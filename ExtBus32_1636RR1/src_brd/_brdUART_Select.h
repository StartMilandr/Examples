#ifndef BRD_SPI_SELECT_H
#define BRD_SPI_SELECT_H

#include "brdDef.h"
#include "brdUart.h"

#define UART_BaudRate  115200

#if defined (USE_MDR1986VE1T)


#elif defined (USE_MDR1986VE9x)

      //  Uart1 TX - PB0
    #define UART1_TX_PORT         BRD_UART1_TX_PB0_PORT
    #define UART1_TX_CLK          BRD_UART1_TX_PB0_CLK 
    #define UART1_TX_PINS         BRD_UART1_TX_PB0_PINS
    #define UART1_TX_FUNC         BRD_UART1_TX_PB0_FUNC
    
    //  Uart1 RX - PB6
    #define UART1_RX_PORT         BRD_UART1_RX_PB6_PORT
    #define UART1_RX_CLK          BRD_UART1_RX_PB6_CLK
    #define UART1_RX_PINS         BRD_UART1_RX_PB6_PINS
    #define UART1_RX_FUNC         BRD_UART1_RX_PB6_FUNC
    
    //  Uart2 TX - PD1
    #define UART2_TX_PORT         BRD_UART2_TX_PF1_PORT
    #define UART2_TX_CLK          BRD_UART2_TX_PF1_CLK
    #define UART2_TX_PINS         BRD_UART2_TX_PF1_PINS
    #define UART2_TX_FUNC         BRD_UART2_TX_PF1_FUNC
    
    //  Uart2 RX - PB1
    #define UART2_RX_PORT         BRD_UART2_RX_PB1_PORT
    #define UART2_RX_CLK          BRD_UART2_RX_PB1_CLK
    #define UART2_RX_PINS         BRD_UART2_RX_PB1_PINS
    #define UART2_RX_FUNC         BRD_UART2_RX_PB1_FUNC

#endif

UART_InitTypeDef brdUartInitStruct = 
{
  115200,                   //  UART_BaudRate
  UART_WordLength8b,        //  UART_WordLength
  UART_StopBits1,           //  UART_StopBits
  UART_Parity_No,           //  UART_Parity
  UART_FIFO_OFF,            //  UART_FIFOMode
  UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE     // UART_HardwareFlowControl
};

PORT_InitTypeDef brdUART_PortStruct = 
{
  0,               //  PORT_Pin
  PORT_OE_IN,           //  PORT_OE_TypeDef 
  PORT_PULL_UP_OFF,     //  PORT_PULL_UP_TypeDef
  PORT_PULL_DOWN_OFF,   //  PORT_PULL_DOWN_TypeDef
  PORT_PD_SHM_OFF,      //  PORT_PD_SHM_TypeDef
  PORT_PD_DRIVER,       //  PORT_PD_TypeDef
  PORT_GFEN_OFF,        //  PORT_GFEN_TypeDef
  PORT_FUNC_PORT,       //  PORT_FUNC_TypeDef
  PORT_SPEED_MAXFAST,   //  PORT_SPEED_TypeDef
  PORT_MODE_DIGITAL     //  PORT_MODE_TypeDef
};

brdPort_Obj brdUART1_PortTX =
{
  UART1_TX_PORT,
  UART1_TX_CLK, 
  UART1_TX_PINS,
  UART1_TX_FUNC,
  0,   // not used
  //  Default settings
  &brdUART_PortStruct
};

brdPort_Obj brdUART1_PortRX =
{
  UART1_RX_PORT,
  UART1_RX_CLK, 
  UART1_RX_PINS,
  UART1_RX_FUNC,
  0,   // not used
  //  Default settings
  &brdUART_PortStruct
};

BrdUART_Obj brdUART1_Obj = 
{
  //  Pins
  &brdUART1_PortTX,
  &brdUART1_PortRX,
  
  //  Uart Init
  MDR_UART1,
  RST_CLK_PCLK_UART1,
  
  //  Uart Settings
  &brdUartInitStruct,
  UART_HCLKdiv1, 
  UART1_IRQn
};

//--------------    Uart2 ----------------
brdPort_Obj brdUART2_PortTX =
{
  UART2_TX_PORT,
  UART2_TX_CLK, 
  UART2_TX_PINS,
  UART2_TX_FUNC,
  0,   // not used
  //  Default settings
  &brdUART_PortStruct
};

brdPort_Obj brdUART2_PortRX =
{
  UART2_RX_PORT,
  UART2_RX_CLK, 
  UART2_RX_PINS,
  UART2_RX_FUNC,
  0,   // not used
  //  Default settings
  &brdUART_PortStruct
};

BrdUART_Obj brdUART2_Obj = 
{
  //  Pins
  &brdUART2_PortTX,
  &brdUART2_PortRX,
  
  //  Uart Init
  MDR_UART2,
  RST_CLK_PCLK_UART2,
  
  //  Uart Settings
  &brdUartInitStruct,
  UART_HCLKdiv1,
  UART2_IRQn
};





#endif //BRD_SPI_SELECT_H
