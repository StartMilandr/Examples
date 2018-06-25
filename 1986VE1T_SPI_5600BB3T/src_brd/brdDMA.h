#ifndef _BRD_DMA_H
#define _BRD_DMA_H

#include "brdDef.h"

#ifndef USE_BOARD_VE_8
  #include <MDR32F9Qx_port.h>
  #include <MDR32F9Qx_rst_clk.h>
  #include <MDR32F9Qx_dma.h>

  #ifdef USE_BOARD_VE_1  
    #define DMA_Channel_TIM1      DMA_Channel_SREQ_TIM1
    #define DMA_Channel_TIM2      DMA_Channel_SREQ_TIM2
    #define DMA_Channel_TIM3      DMA_Channel_SREQ_TIM3
    #define DMA_Channel_TIM4      DMA_Channel_SREQ_TIM4
    
    #define DMA_Channel_SSP2_RX   DMA_Channel_SREQ_SSP2_RX
  #endif

#else
  #include <mdr32f8_port.h>
  #include <mdr32f8_clkctrl.h>
  #include <mdr32f8_dma.h>
   
  #include "brdVE8_toVEx.h"
  
  #define DMA_IRQn  DMA_DONE0_IRQn
    
  void BRD_DMA_ReadRegs(DMAControl *logRegs);  
#endif



void BRD_DMA_Init(void);
void BRD_DMA_InitIRQ(uint32_t priority);    // use priority = 1 by default
void BRD_DMA_Init_Channel (uint32_t DMA_Channel, DMA_ChannelInitTypeDef*  pDMAChannelInitStruct);

//  For fast reinit DMA Channel - save before DMA start and restore on DMA_IRQ
uint32_t BRD_DMA_Read_ChannelCtrl(uint32_t DMA_Channel);
void BRD_DMA_Write_ChannelCtrl(uint32_t DMA_Channel, uint32_t dmaControl);


//  Uncomment if needed
//void BRD_DMA_Read_ChannelCtrlRec(uint32_t DMA_Channel, DMA_CtrlDataTypeDef *chanTable);
//void BRD_DMA_Write_ChannelCtrlRec(uint32_t DMA_Channel, uint32_t *chanTable);

#endif	// _BRD_DMA_H
