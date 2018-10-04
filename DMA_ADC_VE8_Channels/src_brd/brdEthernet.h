#ifndef _BRD_ETHERNET_H
#define _BRD_ETHERNET_H

#ifdef USE_BOARD_VE_8 
  #include <mdr32f8_eth.h>
  #include <MDR1986VE8T.h>
  
  #define ETH_STAT      STAT
  
  #define ETH_R_Head    R_HEAD
  #define ETH_R_Tail    R_TAIL
  #define ETH_X_Head    X_HEAD
  #define ETH_X_Tail    X_TAIL

  typedef MDR_ETH_TypeDef  MDR_ETHERNET_TypeDef;  
#else  
  #include <MDR32F9Qx_port.h>
  #include <MDR32F9Qx_rst_clk.h>
  #include <MDR32F9Qx_eth.h>
#endif 

#define MAX_ETH_TX_DATA_SIZE  1514 + 4  // + 4 - for ControlTX (Length)
#define MAX_ETH_RX_DATA_SIZE (1514 + 4) / 4

#define FRAME_MAC_SIZE  12
#define FRAME_LEN_SIZE   2
#define FRAME_HEAD_SIZE   (FRAME_MAC_SIZE + FRAME_LEN_SIZE)
#define FRAME_CRC_SIZE  4


extern uint8_t  FrameTX[MAX_ETH_TX_DATA_SIZE];
extern uint32_t FrameRX[MAX_ETH_RX_DATA_SIZE];

void BRD_ETH_ClockInit(void);

void BRD_ETH_StructInitDef(ETH_InitTypeDef * ETH_InitStruct, uint8_t *srcMAC);
void BRD_ETH_Init(MDR_ETHERNET_TypeDef * ETHERNETx, ETH_InitTypeDef * ETH_InitStruct);
void BRD_ETH_InitIRQ(MDR_ETHERNET_TypeDef * ETHERNETx, uint32_t IMR_Flags);
void BRD_ETH_Start(MDR_ETHERNET_TypeDef * ETHERNETx);

void BRD_ETH_WaitAutoneg_Completed(MDR_ETHERNET_TypeDef * ETHERNETx);
void BRD_ETH_WaitLink(MDR_ETHERNET_TypeDef * ETHERNETx);

uint32_t BRD_ETH_TryReadFrame(MDR_ETHERNET_TypeDef * ETHERNETx, ETH_StatusPacketReceptionTypeDef * RXStatus);
uint8_t* BRD_ETH_Init_FrameTX(uint8_t *destMAC, uint8_t *srcMAC, uint16_t frameLen, uint16_t *payloadLen);

#endif //_BRD_ETHERNET_H

