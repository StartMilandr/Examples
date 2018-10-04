#include <mdr32f8_clkctrl.h>
#include "brdDef.h"
#include "brdEthernet.h"

uint8_t  FrameTX[MAX_ETH_TX_DATA_SIZE] __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));
uint32_t FrameRX[MAX_ETH_RX_DATA_SIZE] __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));


void BRD_ETH_StructInitDef(ETH_InitTypeDef * ETH_InitStruct, uint8_t *srcMAC)
{
	/* Init ETH_InitStruct members with its default value */
	ETH_StructInit(ETH_InitStruct);

	ETH_InitStruct->ETH_MAC_Address[0] = (srcMAC[1] << 8) | srcMAC[0]; //0x78AB;
	ETH_InitStruct->ETH_MAC_Address[1] = (srcMAC[3] << 8) | srcMAC[2]; //0x3456;
	ETH_InitStruct->ETH_MAC_Address[2] = (srcMAC[5] << 8) | srcMAC[4]; //0x0012;
  
	ETH_InitStruct->ETH_PHY_LB = DISABLE; //ENABLE; //
	ETH_InitStruct->ETH_PHY_DLB = DISABLE;
	ETH_InitStruct->ETH_PHY_HALFD = DISABLE;
	/*ETH_InitStruct.ETH_PHY_EARLY_DV = 0;*///RESERVED
	ETH_InitStruct->ETH_PHY_DIR = ETH_PHY_CONTROL_DIR_DIRECT;
	ETH_InitStruct->ETH_PHY_BASE_2 = ETH_PHY_CONTROL_BASE_2_TWISTED;
	ETH_InitStruct->ETH_PHY_LINK_PERIOD = 0x2;
	ETH_InitStruct->ETH_PHY_EXT_EN = ETH_PHY_CONTROL_EXT_EN_INTER;
	ETH_InitStruct->ETH_PHY_A_SELR = ETH_PHY_CONTROL_A_SELR_INTER;
	ETH_InitStruct->ETH_PHY_A_TRIM = 0x4;
	ETH_InitStruct->ETH_PHY_A_TRIMR = 0x80;
		
	ETH_InitStruct->ETH_Extension_Mode  = DISABLE; //ENABLE;
	ETH_InitStruct->ETH_ColWnd 				  = 0x5;
	ETH_InitStruct->ETH_HalfDuplex_Mode = DISABLE;
	ETH_InitStruct->ETH_Register_CLR 	  = DISABLE;
	ETH_InitStruct->ETH_DBG_XF          = ENABLE;
	ETH_InitStruct->ETH_DBG_RF          = ENABLE;

	ETH_InitStruct->ETH_Loopback_Mode   = DISABLE;
  
  //ETH_InitStruct->ETH_Buffer_Mode 		= ETH_BUFFER_MODE_LINEAR;
  ETH_InitStruct->ETH_Buffer_Mode 		= ETH_BUFFER_MODE_AUTOMATIC_CHANGE_POINTERS;
	//ETH_InitStruct->ETH_Buffer_Mode 		= ETH_BUFFER_MODE_FIFO;  

  ETH_InitStruct->ETH_Dilimiter = 0x1000;

	ETH_InitStruct->ETH_Receive_All_Packets = ENABLE;
	ETH_InitStruct->ETH_Error_CRC_Frames_Reception = ENABLE;
	ETH_InitStruct->ETH_Receiver_Event_Mode = ETH_RECEIVER_EVENT_MODE_PACET_RECEIVED;
	ETH_InitStruct->ETH_Receiver_BE = ETH_RECEIVER_BE_LITTLE_ENDIAN;
		
	ETH_InitStruct->ETH_Transmitter_BE = ETH_TRANSMITTER_BE_LITTLE_ENDIAN;
	ETH_InitStruct->ETH_Transmitter_Event_Mode = ETH_TRANSMITTER_EVENT_MODE_XFIFO_ALMOST_EMPTY;
	ETH_InitStruct->ETH_Automatic_Pad_Strip = ENABLE;
	ETH_InitStruct->ETH_Automatic_Preamble = ENABLE;
	ETH_InitStruct->ETH_Automatic_CRC_Strip = ENABLE;
	ETH_InitStruct->ETH_Automatic_IPG = ENABLE;
	ETH_InitStruct->ETH_Retry_Counter = 0xF;	
}

void BRD_ETH_ClockInit(void)
{
	CLKCTRL_PER0_CLKcmd(CLKCTRL_PER0_CLK_MDR_ENET0_EN, ENABLE);

	ETH_ClockDeInit();
	ETH_PHY_ClockConfig(ETH_PHY_CLOCK_SOURCE_PLL0, ETH_PHY_HCLKdiv1);
	ETH_ClockCMD(ENABLE);
}

void BRD_ETH_Init(MDR_ETHERNET_TypeDef * ETHERNETx, ETH_InitTypeDef * ETH_InitStruct)
{
  ETH_DeInit(ETHERNETx);
  
	ETH_Init(ETHERNETx, ETH_InitStruct);
	
	ETH_PHY_Reset(ETHERNETx);
	ETH_PHYCmd(ETHERNETx, ENABLE);
}

void BRD_ETH_InitIRQ(MDR_ETHERNET_TypeDef * ETHERNETx, uint32_t IMR_Flags)
{
	ETHERNETx->IMR = IMR_Flags;

  if (ETHERNETx == MDR_ETH0)
    NVIC_EnableIRQ(ETH0_IRQn);
  else
    NVIC_EnableIRQ(ETH1_IRQn);
}

void BRD_ETH_Start(MDR_ETHERNET_TypeDef * ETHERNETx)
{
	ETH_Start(ETHERNETx);
}

void BRD_ETH_WaitAutoneg_Completed(MDR_ETHERNET_TypeDef * ETHERNETx)
{
  while (!(ETH_ReadPHYRegister(ETHERNETx, 0x1C, 1) & (1 << 5))) {};
}  

uint32_t BRD_ETH_TryReadFrame(MDR_ETHERNET_TypeDef * ETHERNETx, ETH_StatusPacketReceptionTypeDef * RXStatus)
{
	if(ETHERNETx->R_HEAD != ETHERNETx->R_TAIL)
  {
		RXStatus->Status = ETH_ReceivedFrame(ETHERNETx, FrameRX);
    return 1;
  }
  return 0;
}

uint8_t* BRD_ETH_Init_FrameTX(uint8_t *destMAC, uint8_t *srcMAC, uint16_t frameLen, uint16_t *payloadLen)
{
	uint8_t * ptr_TXFrame = (uint8_t *) &FrameTX[4];
  *payloadLen = frameLen - FRAME_HEAD_SIZE;
  
	//	Count To Send
	*(uint32_t *)&FrameTX[0] = frameLen;
	
	/* Set destanation MAC address */
	ptr_TXFrame[0] 	= destMAC[0];
	ptr_TXFrame[1] 	= destMAC[1];
	ptr_TXFrame[2] 	= destMAC[2];
	ptr_TXFrame[3] 	= destMAC[3];
	ptr_TXFrame[4] 	= destMAC[4];
	ptr_TXFrame[5] 	= destMAC[5];		
	
	/* Set our MAC address */
	ptr_TXFrame[6] 	= srcMAC[0];
	ptr_TXFrame[7] 	= srcMAC[1];
	ptr_TXFrame[8] 	= srcMAC[2];
	ptr_TXFrame[9] 	= srcMAC[3];
	ptr_TXFrame[10] = srcMAC[4];
	ptr_TXFrame[11] = srcMAC[5];	

  // Return dataCount  
	ptr_TXFrame[12] 	= (uint8_t)((*payloadLen) >> 8);
	ptr_TXFrame[13] 	= (uint8_t)((*payloadLen) & 0xFF);	

  // Return DataPtr
  return &ptr_TXFrame[FRAME_HEAD_SIZE];
}
