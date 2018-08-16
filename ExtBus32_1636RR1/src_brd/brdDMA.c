#include "brdDMA.h"

void BRD_DMA_Init(void)
{
  // Включение тактирования модуля DMA
  RST_CLK_PCLKcmd (BRD_DMA_CLOCK_SELECT, ENABLE);
  
// Bug_Fix ???
//#ifdef USE_BOARD_VE_8  
//  CLKCTRL_PER1_CLKcmd(CLKCTRL_PER1_CLK_MDR_SSP0_EN, ENABLE);
//#endif

  // Деинициализация DMA
  DMA_DeInit();	
  
  // Сброс прерывания от DMA
  NVIC_ClearPendingIRQ (DMA_IRQn);  
}  

// Инициализация модуля DMA
void BRD_DMA_Init_Channel (uint32_t DMA_Channel, DMA_ChannelInitTypeDef*  pDMAChannelInitStruct)
{
  // Инициализация канала DMA,
	DMA_Init(DMA_Channel, pDMAChannelInitStruct);
	
  DMA_Cmd(DMA_Channel, ENABLE);
}

void BRD_DMA_InitIRQ(uint32_t priority)
{
  NVIC_SetPriority (DMA_IRQn, priority);
  NVIC_ClearPendingIRQ (DMA_IRQn);  
  NVIC_EnableIRQ (DMA_IRQn); 
}

//// Прототип - Обработчик прерываний от DMA
//void DMA_IRQHandler (void)
//{
//  // Формирование нового цикла аналого-цифровых преобразований
//  DMA_Init (DMA_Channel, &DMAChannelInitStruct);
//  NVIC_ClearPendingIRQ (DMA_IRQn);
//}	

extern DMA_CtrlDataTypeDef DMA_ControlTable[DMA_Channels_Number * (1 + DMA_AlternateData)];

uint32_t BRD_DMA_Read_ChannelCtrl(uint32_t DMA_Channel)
{
	return DMA_ControlTable[DMA_Channel].DMA_Control;
}

void BRD_DMA_Write_ChannelCtrl(uint32_t DMA_Channel, uint32_t dmaControl)
{
	DMA_ControlTable[DMA_Channel].DMA_Control = dmaControl;
}

#ifdef USE_BOARD_VE_8
void BRD_DMA_ReadRegs(DMAControl *logRegs)
{
  logRegs->STATUS         = MDR_DMA->STATUS;
  logRegs->CONFIG         = MDR_DMA->CONFIG;
  logRegs->CTRL_BASE_PTR  = MDR_DMA->CTRL_BASE_PTR;
  logRegs->ALT_CTRL_BASE_PTR  = MDR_DMA->ALT_CTRL_BASE_PTR;
  logRegs->WAITONREG_STATUS   = MDR_DMA->WAITONREG_STATUS;
  logRegs->CHNL_SW_REQUEST    = MDR_DMA->CHNL_SW_REQUEST;
  logRegs->CHNL_USEBURST_SET  = MDR_DMA->CHNL_USEBURST_SET;
  logRegs->CHNL_USEBURST_CLR  = MDR_DMA->CHNL_USEBURST_CLR;
  logRegs->CHNL_REQ_MASK_SET  = MDR_DMA->CHNL_REQ_MASK_SET;
  logRegs->CHNL_REQ_MASK_CLR  = MDR_DMA->CHNL_REQ_MASK_CLR;
  logRegs->CHNL_ENABLE_SET    = MDR_DMA->CHNL_ENABLE_SET;
  logRegs->CHNL_ENABLE_CLR    = MDR_DMA->CHNL_ENABLE_CLR;
  logRegs->CHNL_PRI_ALT_SET   = MDR_DMA->CHNL_PRI_ALT_SET;
  logRegs->CHNL_PRI_ALT_CLR   = MDR_DMA->CHNL_PRI_ALT_CLR;
  logRegs->CHNL_PRIORITY_SET  = MDR_DMA->CHNL_PRIORITY_SET;
  logRegs->CHNL_PRIORITY_CLR  = MDR_DMA->CHNL_PRIORITY_CLR;
  //uint32_t RESERVED[3];
  logRegs->ERR_CLR  = MDR_DMA->ERR_CLR;
  logRegs->CHMUX0   = MDR_DMA->CHMUX0;
  logRegs->CHMUX1   = MDR_DMA->CHMUX1;
  logRegs->CHMUX2   = MDR_DMA->CHMUX2;
  logRegs->CHMUX3   = MDR_DMA->CHMUX3;
  logRegs->CHMUX4   = MDR_DMA->CHMUX4;
  logRegs->CHMUX5   = MDR_DMA->CHMUX5;
  logRegs->CHMUX6   = MDR_DMA->CHMUX6;
  logRegs->CHMUX7   = MDR_DMA->CHMUX7;
}
#endif

//void BRD_DMA_Read_ChannelCtrlRec(uint32_t DMA_Channel, DMA_CtrlDataTypeDef *chanTable)
//{
//	chanTable->DMA_SourceEndAddr = DMA_ControlTable[DMA_Channel].DMA_SourceEndAddr;
//	chanTable->DMA_DestEndAddr   = DMA_ControlTable[DMA_Channel].DMA_DestEndAddr;
//	chanTable->DMA_Control       = DMA_ControlTable[DMA_Channel].DMA_Control;
//}

//void BRD_DMA_Write_ChannelCtrlRec(uint32_t DMA_Channel, uint32_t *chanTable)
//{
//	DMA_ControlTable[DMA_Channel].DMA_SourceEndAddr = chanTable->DMA_SourceEndAddr;
//	DMA_ControlTable[DMA_Channel].DMA_DestEndAddr   = chanTable->DMA_DestEndAddr;
//	DMA_ControlTable[DMA_Channel].DMA_Control       = chanTable->DMA_Control;
//}



