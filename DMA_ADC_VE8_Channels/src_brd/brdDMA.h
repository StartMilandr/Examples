#ifndef _BRD_DMA_H
#define _BRD_DMA_H

#include "brdDef.h"

#ifndef USE_BOARD_VE_8
  #include <MDR32F9Qx_port.h>
  #include <MDR32F9Qx_rst_clk.h>
  #include <MDR32F9Qx_dma.h>

#else
  #include <mdr32f8_port.h>
  #include <mdr32f8_clkctrl.h>
  #include <mdr32f8_dma.h>
   
  #include "brdVE8_toVEx.h"
  
  #define DMA_IRQn  DMA_DONE0_IRQn
#endif



void BRD_DMA_Init(void);
void BRD_DMA_Init_Channel (uint32_t DMA_Channel, DMA_ChannelInitTypeDef*  pDMAChannelInitStruct);

//  For fast reinit DMA Channel - save before DMA start and restore on DMA_IRQ
uint32_t BRD_DMA_Read_ChannelCtrl(uint32_t DMA_Channel);
void BRD_DMA_Write_ChannelCtrl(uint32_t DMA_Channel, uint32_t dmaControl);

void BRD_DMA_ReadRegs(DMAControl *logRegs);

//  Uncomment if needed
//void BRD_DMA_Read_ChannelCtrlRec(uint32_t DMA_Channel, DMA_CtrlDataTypeDef *chanTable);
//void BRD_DMA_Write_ChannelCtrlRec(uint32_t DMA_Channel, uint32_t *chanTable);

#endif	// _BRD_DMA_H
