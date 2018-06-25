#include "brdEthernet.h"

// space for incoming packet
uint8_t  FrameTX[MAX_ETH_TX_DATA_SIZE]    __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));
uint32_t FrameRX[MAX_ETH_RX_DATA_SIZE] __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));


void BRD_ETH_StructInitDef(ETH_InitTypeDef * ETH_InitStruct, uint8_t *srcMAC)
{
	//volatile	uint32_t			ETH_Dilimiter;  
  
	// Init ETH_InitStruct members with its default value
	ETH_StructInit(ETH_InitStruct);
	// Set the speed of the chennel
	ETH_InitStruct->ETH_PHY_Mode = ETH_PHY_MODE_AutoNegotiation;

  //ETH_InitStruct->ETH_Loopback_Mode = ENABLE;
  
	ETH_InitStruct->ETH_Transmitter_RST = SET;
	ETH_InitStruct->ETH_Receiver_RST = SET;
  
	// Set the buffer mode
	ETH_InitStruct->ETH_Buffer_Mode = ETH_BUFFER_MODE_LINEAR;	
	//ETH_InitStruct->ETH_Buffer_Mode = ETH_BUFFER_MODE_FIFO;	
	//ETH_InitStruct->ETH_Buffer_Mode = ETH_BUFFER_MODE_AUTOMATIC_CHANGE_POINTERS;

	// Set the MAC address.
	ETH_InitStruct->ETH_MAC_Address[2] = (srcMAC[5] << 8) | srcMAC[4];
	ETH_InitStruct->ETH_MAC_Address[1] = (srcMAC[3] << 8) | srcMAC[2];
	ETH_InitStruct->ETH_MAC_Address[0] = (srcMAC[1] << 8) | srcMAC[0];

	// Set the buffer size of transmitter and receiver
	ETH_InitStruct->ETH_Dilimiter = 0x1000;

	// Receiver Change settings
	ETH_InitStruct->ETH_Receiver_Event_Mode = ETH_RECEIVER_EVENT_MODE_PACET_RECEIVED;
	
	ETH_InitStruct->ETH_Receive_All_Packets 			  = ENABLE; //DISABLE; //
	ETH_InitStruct->ETH_Short_Frames_Reception 		  = ENABLE; //DISABLE;
	ETH_InitStruct->ETH_Long_Frames_Reception 	    = ENABLE; //DISABLE;
	ETH_InitStruct->ETH_Broadcast_Frames_Reception  = ENABLE; //DISABLE; // ENABLE;
	ETH_InitStruct->ETH_Error_CRC_Frames_Reception  = ENABLE; //DISABLE;
	ETH_InitStruct->ETH_Control_Frames_Reception 	  = ENABLE; //DISABLE;
	ETH_InitStruct->ETH_Unicast_Frames_Reception 	  = ENABLE;
	ETH_InitStruct->ETH_Source_Addr_HASH_Filter 	  = DISABLE; //ENABLE;	
}  


void BRD_ETH_ClockInit(void)
{
	// Reset Ehernet clock settings 
	ETH_ClockDeInit();
	
	// Enable HSE2 oscillator
	RST_CLK_HSE2config(RST_CLK_HSE2_ON);
  while (RST_CLK_HSE2status() != SUCCESS);	
	
  // Config PHY clock
	ETH_PHY_ClockConfig(ETH_PHY_CLOCK_SOURCE_HSE2, ETH_PHY_HCLKdiv1);

	// Init the BRG ETHERNET
	ETH_BRGInit(ETH_HCLKdiv1);

	// Enable the ETHERNET clock
	ETH_ClockCMD(ETH_CLK1, ENABLE);  
}

void BRD_ETH_Init(MDR_ETHERNET_TypeDef * ETHERNETx, ETH_InitTypeDef * ETH_InitStruct)
{	
	// Reset to default ethernet settings
	ETH_DeInit(ETHERNETx);

	// Init the ETHERNET
	ETH_Init(ETHERNETx, ETH_InitStruct);

	// Enable PHY module
	ETH_PHYCmd(ETHERNETx, ENABLE);		
}

void BRD_ETH_InitIRQ(MDR_ETHERNET_TypeDef * ETHERNETx, uint32_t IMR_Flags)
{
	ETHERNETx->ETH_IMR = IMR_Flags;
  NVIC_EnableIRQ(ETHERNET_IRQn);	
}  

void BRD_ETH_Start(MDR_ETHERNET_TypeDef * ETHERNETx)
{
	ETH_Start(ETHERNETx);
}
void BRD_ETH_WaitAutoneg_Completed(MDR_ETHERNET_TypeDef * ETHERNETx)
{ 
  while (!(ETH_ReadPHYRegister(ETHERNETx, 0x1C, 1) & (1 << 5))) {};
}  

void BRD_ETH_WaitLink(MDR_ETHERNET_TypeDef * ETHERNETx)
{ 
  while (!(ETH_ReadPHYRegister(ETHERNETx, 0x1C, 1) & (1 << 2))) {};
}

uint32_t BRD_ETH_TryReadFrame(MDR_ETHERNET_TypeDef * ETHERNETx, ETH_StatusPacketReceptionTypeDef * RXStatus)
{
	if(ETHERNETx->ETH_R_Head != ETHERNETx->ETH_R_Tail)
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
	
	// Ethernet
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

