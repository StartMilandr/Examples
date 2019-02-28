/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 *            (C) COPYRIGHT 2009-2010 ARM Limited.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 *
 *      SVN Information
 *
 *
 *      Revision            : $Revision: 142008 $
 *
 *      Release information : cortexm4_r0p1_00rel0
 *-----------------------------------------------------------------------------
 */

#ifndef __CM4IKMCU_H__
#define __CM4IKMCU_H__

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M4 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn    = -14,    /*!< 2 Non Maskable Interrupt                             */
  HardFault_IRQn         = -13,    /*!< 3 Cortex-M4 Hard Fault Interrupt                     */
  SVCall_IRQn            = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                       */
  PendSV_IRQn            = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                       */
  SysTick_IRQn           = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                   */

/******  CM4IKMCU Cortex-M4 specific Interrupt Numbers ********************************************/
  FT_IF0_IRQn            = 32,
  FT_IF1_IRQn            = 33,
  FT_IF2_IRQn            = 34,
  FT_IF3_IRQn            = 35,
  CLK_IF_IRQn            = 36,
  PVD_IF_IRQn            = 37,
  RTC_IF_IRQn            = 38,
  BKP_IF_IRQn            = 39,
  EXT_INTERROR0_IRQn     = 40,
  EXT_INTERROR1_IRQn     = 41,
  EXT_INTERROR2_IRQn     = 42,
  EXT_INTERROR3_IRQn     = 43,
  EXT_INTERROR4_IRQn     = 44,
  EXT_INTERROR5_IRQn     = 45,
  EXT_INTERROR6_IRQn     = 46,
  EXT_INTERROR7_IRQn     = 47,
  IF_ERR_SCR_IRQn        = 48,
  IF_FIN_SCR_IRQn        = 49,
  DMA_ERR_IRQn           = 50,
  DMA_DONE0_IRQn         = 51,
  DMA_DONE1_IRQn         = 52,
  DMA_DONE2_IRQn         = 53,
  DMA_DONE3_IRQn         = 54,
  DMA_DONE4_IRQn         = 55,
  DMA_DONE5_IRQn         = 56,
  DMA_DONE6_IRQn         = 57,
  DMA_DONE7_IRQn         = 58,
  DMA_DONE8_IRQn         = 59,
  DMA_DONE9_IRQn         = 60,
  DMA_DONE10_IRQn        = 61,
  DMA_DONE11_IRQn        = 62,
  DMA_DONE12_IRQn        = 63,
  DMA_DONE13_IRQn        = 64,
  DMA_DONE14_IRQn        = 65,
  DMA_DONE15_IRQn        = 66,
  DMA_DONE16_IRQn        = 67,
  DMA_DONE17_IRQn        = 68,
  DMA_DONE18_IRQn        = 69,
  DMA_DONE19_IRQn        = 70,
  DMA_DONE20_IRQn        = 71,
  DMA_DONE21_IRQn        = 72,
  DMA_DONE22_IRQn        = 73,
  DMA_DONE23_IRQn        = 74,
  DMA_DONE24_IRQn        = 75,
  DMA_DONE25_IRQn        = 76,
  DMA_DONE26_IRQn        = 77,
  DMA_DONE27_IRQn        = 78,
  DMA_DONE28_IRQn        = 79,
  DMA_DONE29_IRQn        = 80,
  DMA_DONE30_IRQn        = 81,
  DMA_DONE31_IRQn        = 82,
  IRQ_PORTA_IRQn         = 83,
  IRQ_PORTB_IRQn         = 84,
  IRQ_PORTC_IRQn         = 85,
  IRQ_PORTD_IRQn         = 86,
  INT_ETH_IRQn           = 89,
  INT_CAN0_IRQn          = 90,
  INT_CAN1_IRQn          = 91,
  INT_SSP0_IRQn          = 92,
  INT_SSP0_RXINTR_IRQn   = 93,
  INT_SSP0_TXINTR_IRQn   = 94, 
  INT_SSP0_RORINTR_IRQn  = 95, 
  INT_SSP0_RTINTR_IRQn   = 96, 
  INT_SSP0_RNEINTR_IRQn  = 97, 
  INT_SSP0_TFEINTR_IRQn  = 98,
  INT_SSP0_TBSYINTR_IRQn = 99,  
  INT_SSP1_IRQn          = 100,
  INT_SSP1_RXINTR_IRQn   = 101,
  INT_SSP1_TXINTR_IRQn   = 102, 
  INT_SSP1_RORINTR_IRQn  = 103, 
  INT_SSP1_RTINTR_IRQn   = 104, 
  INT_SSP1_RNEINTR_IRQn  = 105, 
  INT_SSP1_TFEINTR_IRQn  = 106,
  INT_SSP1_TBSYINTR_IRQn = 107,
  INT_UART0_IRQn         = 108,
  INT_UART0_TBSYINTR_IRQn= 109,
  INT_UART0_TFEINTR_IRQn = 110,
  INT_UART0_RNEINTR_IRQn = 111,
  INT_UART0_EINTR_IRQn   = 112,
  INT_UART0_RTINTR_IRQn  = 113,
  INT_UART0_TXINTR_IRQn  = 114,
  INT_UART0_RXINTR_IRQn  = 115,
  INT_UART0_MSINTR_IRQn  = 116,
  INT_UART1_IRQn         = 117,
  INT_UART1_TBSYINTR_IRQn= 118,
  INT_UART1_TFEINTR_IRQn = 119,
  INT_UART1_RNEINTR_IRQn = 120,
  INT_UART1_EINTR_IRQn   = 121,
  INT_UART1_RTINTR_IRQn  = 122,
  INT_UART1_TXINTR_IRQn  = 123,
  INT_UART1_RXINTR_IRQn  = 124,
  INT_UART1_MSINTR_IRQn  = 125,
  INT_UART2_IRQn         = 126,
  INT_UART2_TBSYINTR_IRQn= 127,
  INT_UART2_TFEINTR_IRQn = 128,
  INT_UART2_RNEINTR_IRQn = 129,
  INT_UART2_EINTR_IRQn   = 130,
  INT_UART2_RTINTR_IRQn  = 131,
  INT_UART2_TXINTR_IRQn  = 132,
  INT_UART2_RXINTR_IRQn  = 133,
  INT_UART2_MSINTR_IRQn  = 134,
  INT_UART3_IRQn         = 135,
  INT_UART3_TBSYINTR_IRQn= 136,
  INT_UART3_TFEINTR_IRQn = 137,
  INT_UART3_RNEINTR_IRQn = 138,
  INT_UART3_EINTR_IRQn   = 139,
  INT_UART3_RTINTR_IRQn  = 140,
  INT_UART3_TXINTR_IRQn  = 141,
  INT_UART3_RXINTR_IRQn  = 142,
  INT_UART3_MSINTR_IRQn  = 143,
  INT_USB_IRQn           = 144,
  INT_MIL0_IRQn          = 145,
  INT_DAC0_IRQn          = 146,
  INT_DAC1_IRQn          = 147,
  INT_DAC2_IRQn          = 148,
  INT_DAC3_IRQn          = 149,
  INT_DAC0_FIFO_IRQn     = 150,
  INT_DAC1_FIFO_IRQn     = 151,
  INT_DAC2_FIFO_IRQn     = 152,
  INT_DAC3_FIFO_IRQn     = 153,
  INT_TMR0_IRQn          = 154,
  INT_TMR1_IRQn          = 155,
  INT_TMR2_IRQn          = 156,
  INT_TMR3_IRQn          = 157,
  INT_QEP0_IRQn          = 158,
  INT_QEP1_IRQn          = 159,
  INT_CAP0_IRQn          = 162,
  INT_CAP1_IRQn          = 163,
  INT_CAP2_IRQn          = 164,
  INT_CAP3_IRQn          = 165,
  INT_EPWM9_IRQn         = 166,
  INT_EPWM8_IRQn         = 167,
  INT_EPWM7_IRQn         = 168,
  INT_EPWM6_IRQn         = 169,
  INT_EPWM5_IRQn         = 170,
  INT_EPWM4_IRQn         = 171,
  INT_EPWM3_IRQn         = 172,
  INT_EPWM2_IRQn         = 173,
  INT_EPWM1_IRQn         = 174,
  INT_EPWM_TZ9_IRQn      = 175,
  INT_EPWM_TZ8_IRQn      = 176,
  INT_EPWM_TZ7_IRQn      = 177,
  INT_EPWM_TZ6_IRQn      = 178,
  INT_EPWM_TZ5_IRQn      = 179,
  INT_EPWM_TZ4_IRQn      = 180,
  INT_EPWM_TZ3_IRQn      = 181,
  INT_EPWM_TZ2_IRQn      = 182,
  INT_EPWM_TZ1_IRQn      = 183,
  INT_EPWM_FIFO9_IRQn    = 184,
  INT_EPWM_FIFO8_IRQn    = 185,
  INT_EPWM_FIFO7_IRQn    = 186,
  INT_EPWM_FIFO6_IRQn    = 187,
  INT_EPWM_FIFO5_IRQn    = 188,
  INT_EPWM_FIFO4_IRQn    = 189,
  INT_EPWM_FIFO3_IRQn    = 190,
  INT_EPWM_FIFO2_IRQn    = 191,
  INT_EPWM_FIFO1_IRQn    = 192,
  INT_CMP0_IRQn          = 193,
  INT_CMP1_IRQn          = 194,
  INT_CMP2_IRQn          = 195,
  INT_CMP3_IRQn          = 196,
  INT_ADC12_IRQn         = 197,
  INT_ADC_FIFO12_IRQn    = 198,
  INT_ADC11_IRQn         = 199,
  INT_ADC_FIFO11_IRQn    = 200,
  INT_ADC10_IRQn         = 201,
  INT_ADC_FIFO10_IRQn    = 202,
  INT_ADC02_IRQn         = 203,
  INT_ADC_FIFO02_IRQn    = 204,
  INT_ADC01_IRQn         = 205,
  INT_ADC_FIFO01_IRQn    = 206,
  INT_ADC00_IRQn         = 207,
  INT_ADC_FIFO00_IRQn    = 208, 
  INT_CRCD_IRQn          = 209,
  INT_CANFD_IRQn         = 210,
  INT_MIL1_IRQn          = 211
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M4 Processor and Core Peripherals */
#define __MPU_PRESENT           1       /*!< cm4ikmcu does not provide a MPU present or not       */
#define __NVIC_PRIO_BITS        2       /*!< cm4ikmcu Supports 2 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used         */


#include "core_cm4.h"                   /* Cortex-M4 processor and core peripherals               */
#include "system_cm4ikmcu.h"            /* cm4ikmcu System                                        */



/**
 * Initialize the system clock
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system
 *         Initialize the PLL and update the SystemFrequency variable
 */
extern void SystemInit (void);


/**************************************************************************************************/
/*                                  Memory map                                                    */
/**************************************************************************************************/
/* Peripheral and SRAM base address */
#define SRAM_BASE                 ((uint32_t)0x20000000)
#define PERIPH_BASE               ((uint32_t)0x40000000)
#define CORE_BASE                 ((uint32_t)0xe0000000)

#define SMPID                     ((volatile uint32_t) *((uint32_t *)0xe00fe000))
#define SMPID_BASE                ((uint32_t) 0xe00fe000)

/**************************************************************************************************/
/*                Device Specific Peripheral registers structures                                 */
/**************************************************************************************************/

/*--------------------- General Purpose Input and Ouptut ---------------------*/
typedef union
{
  __IO uint32_t WORD;
  __IO uint16_t HALFWORD[2];
  __IO uint8_t  BYTE[4];
} GPIO_Data_TypeDef;

typedef struct
{
  GPIO_Data_TypeDef DATA [256];
  GPIO_Data_TypeDef DIR;
  uint32_t RESERVED[3];
  GPIO_Data_TypeDef IE;
} GPIO_TypeDef;

#define GPIO_BASE                 (PERIPH_BASE + 0x0e000)

#define GPIO0_BASE                (GPIO_BASE   + 0x0000)
#define GPIO1_BASE                (GPIO_BASE   + 0x0800)
#define GPIO2_BASE                (GPIO_BASE   + 0x1000)

#define GPIO0                     ((GPIO_TypeDef *) GPIO0_BASE)
#define GPIO1                     ((GPIO_TypeDef *) GPIO1_BASE)
#define GPIO2                     ((GPIO_TypeDef *) GPIO2_BASE)

//---DMA-------------------------------------------------------------------------------------------;
/***
*  DMA control
**/
typedef struct
{
  __IO  uint32_t STATUS;
  __IO  uint32_t CONFIG;
  __IO  uint32_t CTRL_BASE_PTR;
  __IO  uint32_t ALT_CTRL_BASE_PTR;
  __IO  uint32_t WAITONREG_STATUS;
  __IO  uint32_t CHNL_SW_REQUEST;
  __IO  uint32_t CHNL_USEBURST_SET;
  __IO  uint32_t CHNL_USEBURST_CLR;
  __IO  uint32_t CHNL_REQ_MASK_SET;
  __IO  uint32_t CHNL_REQ_MASK_CLR;
  __IO  uint32_t CHNL_ENABLE_SET;
  __IO  uint32_t CHNL_ENABLE_CLR;
  __IO  uint32_t CHNL_PRI_ALT_SET;
  __IO  uint32_t CHNL_PRI_ALT_CLR;
  __IO  uint32_t CHNL_PRIORITY_SET;
  __IO  uint32_t CHNL_PRIORITY_CLR;
  uint32_t RESERVED[3];
  __IO  uint32_t ERR_CLR;
  __IO  uint32_t CHMUX0;
  __IO  uint32_t CHMUX1;
  __IO  uint32_t CHMUX2;
  __IO  uint32_t CHMUX3;
  __IO  uint32_t CHMUX4;
  __IO  uint32_t CHMUX5;
  __IO  uint32_t CHMUX6;
  __IO  uint32_t CHMUX7;
} DMAControl;

#define DMA_CNTR_BASE             (( uint32_t) 0xe0042000)

#define DMA                       ((DMAControl *) DMA_CNTR_BASE)

/***
*  DMA Primary data structure
**/

typedef struct
{
  __IO  uint32_t PRIMARY_CH0_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH0_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH0_CONTROL;
  __IO  uint32_t PRIMARY_CH0_UNUSED;

  __IO  uint32_t PRIMARY_CH1_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH1_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH1_CONTROL;
  __IO  uint32_t PRIMARY_CH1_UNUSED;

  __IO  uint32_t PRIMARY_CH2_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH2_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH2_CONTROL;
  __IO  uint32_t PRIMARY_CH2_UNUSED;

  __IO  uint32_t PRIMARY_CH3_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH3_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH3_CONTROL;
  __IO  uint32_t PRIMARY_CH3_UNUSED;

  __IO  uint32_t PRIMARY_CH4_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH4_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH4_CONTROL;
  __IO  uint32_t PRIMARY_CH4_UNUSED;

  __IO  uint32_t PRIMARY_CH5_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH5_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH5_CONTROL;
  __IO  uint32_t PRIMARY_CH5_UNUSED;

  __IO  uint32_t PRIMARY_CH6_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH6_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH6_CONTROL;
  __IO  uint32_t PRIMARY_CH6_UNUSED;

  __IO  uint32_t PRIMARY_CH7_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH7_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH7_CONTROL;
  __IO  uint32_t PRIMARY_CH7_UNUSED;

  __IO  uint32_t PRIMARY_CH8_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH8_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH8_CONTROL;
  __IO  uint32_t PRIMARY_CH8_UNUSED;

  __IO  uint32_t PRIMARY_CH9_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH9_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH9_CONTROL;
  __IO  uint32_t PRIMARY_CH9_UNUSED;

  __IO  uint32_t PRIMARY_CH10_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH10_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH10_CONTROL;
  __IO  uint32_t PRIMARY_CH10_UNUSED;

  __IO  uint32_t PRIMARY_CH11_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH11_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH11_CONTROL;
  __IO  uint32_t PRIMARY_CH11_UNUSED;

  __IO  uint32_t PRIMARY_CH12_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH12_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH12_CONTROL;
  __IO  uint32_t PRIMARY_CH12_UNUSED;

  __IO  uint32_t PRIMARY_CH13_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH13_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH13_CONTROL;
  __IO  uint32_t PRIMARY_CH13_UNUSED;

  __IO  uint32_t PRIMARY_CH14_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH14_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH14_CONTROL;
  __IO  uint32_t PRIMARY_CH14_UNUSED;

  __IO  uint32_t PRIMARY_CH15_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH15_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH15_CONTROL;
  __IO  uint32_t PRIMARY_CH15_UNUSED;

  __IO  uint32_t PRIMARY_CH16_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH16_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH16_CONTROL;
  __IO  uint32_t PRIMARY_CH16_UNUSED;

  __IO  uint32_t PRIMARY_CH17_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH17_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH17_CONTROL;
  __IO  uint32_t PRIMARY_CH17_UNUSED;

  __IO  uint32_t PRIMARY_CH18_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH18_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH18_CONTROL;
  __IO  uint32_t PRIMARY_CH18_UNUSED;

  __IO  uint32_t PRIMARY_CH19_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH19_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH19_CONTROL;
  __IO  uint32_t PRIMARY_CH19_UNUSED;

  __IO  uint32_t PRIMARY_CH20_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH20_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH20_CONTROL;
  __IO  uint32_t PRIMARY_CH20_UNUSED;

  __IO  uint32_t PRIMARY_CH21_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH21_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH21_CONTROL;
  __IO  uint32_t PRIMARY_CH21_UNUSED;

  __IO  uint32_t PRIMARY_CH22_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH22_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH22_CONTROL;
  __IO  uint32_t PRIMARY_CH22_UNUSED;

  __IO  uint32_t PRIMARY_CH23_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH23_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH23_CONTROL;
  __IO  uint32_t PRIMARY_CH23_UNUSED;

  __IO  uint32_t PRIMARY_CH24_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH24_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH24_CONTROL;
  __IO  uint32_t PRIMARY_CH24_UNUSED;

  __IO  uint32_t PRIMARY_CH25_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH25_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH25_CONTROL;
  __IO  uint32_t PRIMARY_CH25_UNUSED;

  __IO  uint32_t PRIMARY_CH26_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH26_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH26_CONTROL;
  __IO  uint32_t PRIMARY_CH26_UNUSED;

  __IO  uint32_t PRIMARY_CH27_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH27_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH27_CONTROL;
  __IO  uint32_t PRIMARY_CH27_UNUSED;

  __IO  uint32_t PRIMARY_CH28_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH28_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH28_CONTROL;
  __IO  uint32_t PRIMARY_CH28_UNUSED;

  __IO  uint32_t PRIMARY_CH29_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH29_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH29_CONTROL;
  __IO  uint32_t PRIMARY_CH29_UNUSED;

  __IO  uint32_t PRIMARY_CH30_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH30_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH30_CONTROL;
  __IO  uint32_t PRIMARY_CH30_UNUSED;

  __IO  uint32_t PRIMARY_CH31_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH31_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH31_CONTROL;
  __IO  uint32_t PRIMARY_CH31_UNUSED;
} DMA_PrimaryData_TypeDef;

/***
*  DMA Alternate data structure
**/

typedef struct
{
  __IO  uint32_t ALTER_CH0_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH0_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH0_CONTROL;
  __IO  uint32_t ALTER_CH0_UNUSED;

  __IO  uint32_t ALTER_CH1_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH1_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH1_CONTROL;
  __IO  uint32_t ALTER_CH1_UNUSED;

  __IO  uint32_t ALTER_CH2_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH2_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH2_CONTROL;
  __IO  uint32_t ALTER_CH2_UNUSED;

  __IO  uint32_t ALTER_CH3_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH3_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH3_CONTROL;
  __IO  uint32_t ALTER_CH3_UNUSED;

  __IO  uint32_t ALTER_CH4_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH4_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH4_CONTROL;
  __IO  uint32_t ALTER_CH4_UNUSED;

  __IO  uint32_t ALTER_CH5_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH5_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH5_CONTROL;
  __IO  uint32_t ALTER_CH5_UNUSED;

  __IO  uint32_t ALTER_CH6_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH6_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH6_CONTROL;
  __IO  uint32_t ALTER_CH6_UNUSED;

  __IO  uint32_t ALTER_CH7_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH7_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH7_CONTROL;
  __IO  uint32_t ALTER_CH7_UNUSED;

  __IO  uint32_t ALTER_CH8_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH8_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH8_CONTROL;
  __IO  uint32_t ALTER_CH8_UNUSED;

  __IO  uint32_t ALTER_CH9_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH9_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH9_CONTROL;
  __IO  uint32_t ALTER_CH9_UNUSED;

  __IO  uint32_t ALTER_CH10_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH10_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH10_CONTROL;
  __IO  uint32_t ALTER_CH10_UNUSED;

  __IO  uint32_t ALTER_CH11_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH11_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH11_CONTROL;
  __IO  uint32_t ALTER_CH11_UNUSED;

  __IO  uint32_t ALTER_CH12_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH12_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH12_CONTROL;
  __IO  uint32_t ALTER_CH12_UNUSED;

  __IO  uint32_t ALTER_CH13_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH13_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH13_CONTROL;
  __IO  uint32_t ALTER_CH13_UNUSED;

  __IO  uint32_t ALTER_CH14_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH14_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH14_CONTROL;
  __IO  uint32_t ALTER_CH14_UNUSED;

  __IO  uint32_t ALTER_CH15_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH15_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH15_CONTROL;
  __IO  uint32_t ALTER_CH15_UNUSED;

  __IO  uint32_t ALTER_CH16_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH16_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH16_CONTROL;
  __IO  uint32_t ALTER_CH16_UNUSED;

  __IO  uint32_t ALTER_CH17_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH17_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH17_CONTROL;
  __IO  uint32_t ALTER_CH17_UNUSED;

  __IO  uint32_t ALTER_CH18_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH18_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH18_CONTROL;
  __IO  uint32_t ALTER_CH18_UNUSED;

  __IO  uint32_t ALTER_CH19_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH19_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH19_CONTROL;
  __IO  uint32_t ALTER_CH19_UNUSED;

  __IO  uint32_t ALTER_CH20_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH20_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH20_CONTROL;
  __IO  uint32_t ALTER_CH20_UNUSED;

  __IO  uint32_t ALTER_CH21_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH21_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH21_CONTROL;
  __IO  uint32_t ALTER_CH21_UNUSED;

  __IO  uint32_t ALTER_CH22_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH22_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH22_CONTROL;
  __IO  uint32_t ALTER_CH22_UNUSED;

  __IO  uint32_t ALTER_CH23_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH23_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH23_CONTROL;
  __IO  uint32_t ALTER_CH23_UNUSED;

  __IO  uint32_t ALTER_CH24_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH24_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH24_CONTROL;
  __IO  uint32_t ALTER_CH24_UNUSED;

  __IO  uint32_t ALTER_CH25_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH25_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH25_CONTROL;
  __IO  uint32_t ALTER_CH25_UNUSED;

  __IO  uint32_t ALTER_CH26_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH26_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH26_CONTROL;
  __IO  uint32_t ALTER_CH26_UNUSED;

  __IO  uint32_t ALTER_CH27_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH27_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH27_CONTROL;
  __IO  uint32_t ALTER_CH27_UNUSED;

  __IO  uint32_t ALTER_CH28_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH28_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH28_CONTROL;
  __IO  uint32_t ALTER_CH28_UNUSED;

  __IO  uint32_t ALTER_CH29_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH29_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH29_CONTROL;
  __IO  uint32_t ALTER_CH29_UNUSED;

  __IO  uint32_t ALTER_CH30_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH30_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH30_CONTROL;
  __IO  uint32_t ALTER_CH30_UNUSED;

  __IO  uint32_t ALTER_CH31_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH31_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH31_CONTROL;
  __IO  uint32_t ALTER_CH31_UNUSED;
} DMA_AlterData_TypeDef;
/***

//---Cache-----------------------------------------------------------------------------------------;
*  Cache control
**/
typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t CNTL;
  __I uint32_t HIT_CNT;
  __I uint32_t MISS_CNT;
  uint32_t RESERVED[4];
  __IO  uint32_t ECC_CNTL;
  __IO  uint32_t ECC_ADDR;
  __IO  uint32_t ECC_DATA;
  __IO  uint32_t ECC_ECC;
} CacheControl;

#define ICACHE_BASE               (( uint32_t) 0xe0044000)
#define DCACHE_BASE               (( uint32_t) 0xe0045000)

#define ICACHE                    ((CacheControl *) ICACHE_BASE)
#define DCACHE                    ((CacheControl *) DCACHE_BASE)

#define CC_CACHE_ENABLE ((uint32_t)   0x1 )
#define CC_CACHE_CLR    ((uint32_t) (1<<1))
#define CC_OTP_ENABLE   ((uint32_t) (1<<2))
#define CC_EXTB_ENABLE  ((uint32_t) (1<<3))
#define CC_HIT_CLR      ((uint32_t) (1<<4))
#define CC_MISS_CLR     ((uint32_t) (1<<5))
#define CC_KEY          ((uint32_t) 0x8555aaa1)

//---SCRABER---------------------------------------------------------------------------------------;
/***
*  SCRABER control
**/
typedef struct
{
  __IO  uint32_t CNTRL;
  __IO  uint32_t S_ADDR;
  __IO  uint32_t F_ADDR;
  __IO  uint32_t DATA;
  __IO  uint32_t SECC;
} SCRControl;

#define SCR_CNTR_BASE     (( uint32_t) 0xe0043000)

#define SCR_CNTR      ((SCRControl *) SCR_CNTR_BASE)


//---MDR_ETH---------------------------------------------------------------------------------------;
/***
*  MDR_ETH control
**/
typedef struct
{
  __IO  uint16_t DILIMETR;
  __IO  uint16_t MAC_T;
  __IO  uint16_t MAC_M;
  __IO  uint16_t MAC_H;
  __IO  uint16_t HASH0;
  __IO  uint16_t HASH1;
  __IO  uint16_t HASH2;
  __IO  uint16_t HASH3;
  __IO  uint16_t IPG;
  __IO  uint16_t PSC;
  __IO  uint16_t BAG;
  __IO  uint16_t JITTERWND;
  __IO  uint16_t R_CFG;
  __IO  uint16_t X_CFG;
  __IO  uint32_t G_CFG;//__IO uint16_t G_CFGl;__IO  uint16_t G_CFGh;
  __IO  uint16_t IMR;
  __IO  uint16_t IFR;
  __IO  uint16_t MDIO_CTRL;
  __IO  uint16_t MDIO_DATA;
  __IO  uint16_t R_HEAD;
  __IO  uint16_t X_TAIL;
  __IO  uint16_t R_TAIL;
  __IO  uint16_t X_HEAD;
  __IO  uint16_t STAT;
  __IO  uint16_t RCOUNTER;
  __IO  uint16_t PHY_CONTROL;
  __IO  uint16_t PHY_STATUS;
  __IO  uint16_t PHY_CNTR_A;
}MDR_ETH_TypeDef;

#define MDR_ETH_BASE              (SRAM_BASE + 0x1000000)

#define MDR_ETH0_BASE             (MDR_ETH_BASE + 0x00000)

#define MDR_ETH0                  ((MDR_ETH_TypeDef *) MDR_ETH0_BASE)

//---USB-------------------------------------------------------------------------------------------;
/****
/ USB controller interface
**/
typedef struct
{
   __IO uint8_t  TxFuncAddr;
        uint8_t  UNUSED1;
   __IO uint8_t  TxHudAddr;
   __IO uint8_t  TxHudPort;
        uint32_t UNUSED2;
} USB_TAR0_struct;

typedef struct
{
   __IO uint8_t TxFuncAddr;
        uint8_t UNUSED1;
   __IO uint8_t TxHudAddr;
   __IO uint8_t TxHudPort;
   __IO uint8_t RxFuncAddr;
        uint8_t UNUSED2;
   __IO uint8_t RxHudAddr;
   __IO uint8_t RxHudPort;
} USB_TAR_struct;

typedef struct
{
  /* Common USB registers */
  __IO uint8_t  FADDR;
  __IO uint8_t  POWER;
  __I  uint16_t INTRTX;
  __I  uint16_t INTRRX;
  __IO uint16_t INTRTXE;
  __IO uint16_t INTRRXE;
  __I  uint8_t  INTRUSB;
  __IO uint8_t  INTRUSBE;
  __I  uint16_t FRAME;
  __IO uint8_t  INDEX;
  __IO uint8_t  TESTMODE;
  /* Indexed registers */
  __IO uint16_t TXMAXP;
  __IO uint16_t CSR0_TXCSR;
  __IO uint16_t RXMAXP;
  __IO uint16_t RXCSR;
  __I  uint16_t COUNT0_RXCOUNT;
  __IO uint8_t  TYPE0_TXTYPE;
  __IO uint8_t  NAKLIMIT0_TXINTERVAL;
  __IO uint8_t  RXTYPE;
  __IO uint8_t  RXINTERVAL;
       uint8_t  UNUSED1;
  __I  uint8_t  CONFIGDATA_FIFOSIZE;
  /* FIFOs */
  __IO uint32_t FIFO[4];
       uint32_t UNUSED2[12];
  /* OTG, Dynamic FIFO, Version & Vendor registers */
  __IO uint8_t  DEVCTL;
       uint8_t  UNUSED3;
  __IO uint8_t  TXFIFOSZ;
  __IO uint8_t  RXFIFOSZ;
  __IO uint16_t TXFIFOADD;
  __IO uint16_t RXFIFOADD;
       uint32_t UNUSED4;
  __I  uint16_t HWVERS;
       uint16_t UNUSED5;
       uint32_t UNUSED6[4];
  /* */
USB_TAR0_struct TAR0;
USB_TAR_struct  TAR[3];
}
USB_Typedef;

#define MDR_USB_BASE              (SRAM_BASE + 0x1000000)

#define MDR_USB0_BASE             (MDR_USB_BASE + 0x10000)

#define MDR_USB0                  ((USB_Typedef *) MDR_USB0_BASE)

/**************************************************************************************************/
/*                         Peripheral declaration                                                 */
/**************************************************************************************************/
//---CLOCK-----------------------------------------------------------------------------------------;
/***
*   CLOCK Control
**/

typedef struct
{
  __IO  uint32_t CLK;
  __IO  uint32_t CHK0;
  __IO  uint32_t CHK1;
  __IO  uint32_t CHK2;
  __IO  uint32_t STAT;
}MDR_CLK_TypeDef;

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t MAX_CLK;
  __IO  uint32_t CPU_CLK;
  __IO  uint32_t PER0_CLK;
  __IO  uint32_t PER1_CLK;

  __IO  uint32_t CPU_CHK0;
  __IO  uint32_t CPU_CHK1;
  __IO  uint32_t CPU_CHK2;
  __IO  uint32_t CPU_STAT;

  MDR_CLK_TypeDef LSI;

  __IO  uint32_t HSI_STAT;

  MDR_CLK_TypeDef LSE;

  MDR_CLK_TypeDef HSE[2];

  MDR_CLK_TypeDef PLL[4];

  __IO  uint32_t EMAC0_CLK;
  __IO  uint32_t USB0_CLK;
  __IO  uint32_t USBMAC_CLK;
  __IO  uint32_t RTC0_CLK;

  __IO  uint32_t SSP0_CLK;
  __IO  uint32_t SSP1_CLK;

  __IO  uint32_t CAN0_CLK;
  __IO  uint32_t CAN1_CLK;

  __IO  uint32_t UART0_CLK;
  __IO  uint32_t UART1_CLK;
  __IO  uint32_t UART2_CLK;
  __IO  uint32_t UART3_CLK;

  __IO  uint32_t MIL0_CLK;

  __IO  uint32_t TIM0_CLK;
  __IO  uint32_t TIM1_CLK;
  __IO  uint32_t TIM2_CLK;
  __IO  uint32_t RESERVED0;
  __IO  uint32_t TIM3_CLK;

  __IO  uint32_t CAP0_CLK;
  __IO  uint32_t CAP1_CLK;
  __IO  uint32_t CAP2_CLK;
  __IO  uint32_t CAP3_CLK;

  __IO  uint32_t QEP0_CLK;
  __IO  uint32_t QEP1_CLK;

  __IO  uint32_t PWM0_CLK;
  __IO  uint32_t PWM1_CLK;
  __IO  uint32_t PWM2_CLK;
  __IO  uint32_t PWM3_CLK;
  __IO  uint32_t PWM4_CLK;
  __IO  uint32_t PWM5_CLK;
  __IO  uint32_t PWM6_CLK;
  __IO  uint32_t PWM7_CLK;
  __IO  uint32_t PWM8_CLK;

  __IO  uint32_t ADC0_CLK;
  __IO  uint32_t RESERVED1[32];
  __IO  uint32_t ADC1_CLK;
  __IO  uint32_t ADC2_CLK;
  __IO  uint32_t CRDC_CLK;
  __IO  uint32_t CANFD_CLK;
  __IO  uint32_t CRPT_CLK;
} CLKControl;

#define CLK_CNTR_BASE             (PERIPH_BASE + 0x00000)

#define CLK_CNTR                  ((CLKControl *) CLK_CNTR_BASE)

//---BKP-------------------------------------------------------------------------------------------;
/***
*  BKP control
**/

typedef struct
{
  __IO  uint32_t REG_xx[60];
  __IO  uint32_t KEY;
  __IO  uint32_t REG_64_TMR0;
  __IO  uint32_t REG_64_TMR1;
  __IO  uint32_t REG_64_TMR2;

  __IO  uint32_t REG_60_TMR0;
  __IO  uint32_t REG_61_TMR0;
  __IO  uint32_t REG_62_TMR0;
  __IO  uint32_t REG_63_TMR0;
  
  __IO  uint32_t REG_60_TMR1;
  __IO  uint32_t REG_61_TMR1;
  __IO  uint32_t REG_62_TMR1;
  __IO  uint32_t REG_63_TMR1;

  __IO  uint32_t REG_60_TMR2;
  __IO  uint32_t REG_61_TMR2;
  __IO  uint32_t REG_62_TMR2;
  __IO  uint32_t REG_63_TMR2;

  __IO  uint32_t RTC_CNT_TMR0;
  __IO  uint32_t RTC_DIV_TMR0;
  __IO  uint32_t RTC_PRL_TMR0;
  __IO  uint32_t RTC_ALRM_TMR0;
  __IO  uint32_t RTC_CS_TMR0;

  __IO  uint32_t RESERV_1[3];

  __IO  uint32_t RTC_CNT_TMR1;
  __IO  uint32_t RTC_DIV_TMR1;
  __IO  uint32_t RTC_PRL_TMR1;
  __IO  uint32_t RTC_ALRM_TMR1;
  __IO  uint32_t RTC_CS_TMR1;

  __IO  uint32_t RESERV_2[3];

  __IO  uint32_t RTC_CNT_TMR2;
  __IO  uint32_t RTC_DIV_TMR2;
  __IO  uint32_t RTC_PRL_TMR2;
  __IO  uint32_t RTC_ALRM_TMR2;
  __IO  uint32_t RTC_CS_TMR2;

  __IO  uint32_t RESERV_3[3];
  __IO  uint32_t BKP_PWR_CNTR0;
  __IO  uint32_t BKP_PWR_CNTR1;
  __IO  uint32_t RESERV_4;
  __IO  uint32_t BKP_PWR_CNTR2;
} BKPControl;


#define BKP_KEY                   ((uint32_t) 0x8555aaa1)

#define BKP_BASE                  (PERIPH_BASE + 0x01000)

#define BKP                       ((BKPControl *) BKP_BASE)

//---PWR-------------------------------------------------------------------------------------------;
/***
*  PWR control
**/

typedef struct
{
  __IO  uint32_t KEY;

  __IO  uint32_t CNTR0;
  __IO  uint32_t CNTR1;
  __IO  uint32_t CNTR2;

  __IO  uint32_t STAT;

  __IO  uint32_t ULIMIT;
  __IO  uint32_t CLIMIT;
} PWRControl;


#define PWR_BASE                  (PERIPH_BASE + 0x02000)

#define PWR                       ((PWRControl *) PWR_BASE)

//---FT--------------------------------------------------------------------------------------------;
/***
*  FT control
**/
typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t CONTROL;
  __IO  uint32_t STATUS;
  __IO  uint32_t TIMEOUT;
  __IO  uint32_t TICKCNT;
  __IO  uint32_t FIRSTEVENT;
  __IO  uint32_t LASTEVENT;
  __IO  uint32_t TIMEOUTCNT;
  __IO  uint32_t EVENT[13];
  __IO  uint32_t RESET_EVENT0;
  __IO  uint32_t RESET_EVENT1;
  __IO  uint32_t RESET_EVENT2;
  __IO  uint32_t RESET_EVENT3;
  __IO  uint32_t RESET_EVENT4;
  __IO  uint32_t IE_EVENT5;
  __IO  uint32_t IE_EVENT6;
  __IO  uint32_t IE_EVENT7;
  __IO  uint32_t IE_EVENT8;
  __IO  uint32_t IE_EVENT9;
  __IO  uint32_t IE_EVENT10;
  __IO  uint32_t IE_EVENT11;
  __IO  uint32_t IE_EVENT12;
  __IO  uint32_t FT_STAT0;
  __IO  uint32_t FT_STAT1;
} FTControl;

#define FT_CNTR_BASE              (PERIPH_BASE + 0x03000)

#define FT_CNTR                   ((FTControl *) FT_CNTR_BASE)

//---WDT-------------------------------------------------------------------------------------------;
/***
*  WDT control
**/

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t PRL;
  __IO  uint32_t EN;
  __IO  uint32_t CNT;
} WDTControl;

#define WDT_BASE                  (PERIPH_BASE + 0x04000)

#define WDT                       ((WDTControl *) WDT_BASE)

//---FLASH-----------------------------------------------------------------------------------------;
/***
*  OTP control
**/

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t CNTR;
  __IO  uint32_t ADR;
  __IO  uint32_t WDATA3;
  __IO  uint32_t WDATA2;
  __IO  uint32_t WDATA1;
  __IO  uint32_t WDATA0;
  __IO  uint32_t WECC0;
  __IO  uint32_t WECC1;
  __IO  uint32_t RDATA3;
  __IO  uint32_t RDATA2;
  __IO  uint32_t RDATA1;
  __IO  uint32_t RDATA0;
  __IO  uint32_t RECC0;
  __IO  uint32_t RECC1;
  __IO  uint32_t ECCCS;
  __IO  uint32_t ECCADR;
  __IO  uint32_t ECCDATA;
  __IO  uint32_t ECCECC;
  __IO  uint32_t BLOCK;
} FLASHControl;


#define FLASH_BASE                (PERIPH_BASE + 0x06000)

#define FLASH1_CNTR_BASE          (FLASH_BASE   + 0x0000)

#define FLASH1_CNTR               ((FLASHControl *) FLASH1_CNTR_BASE)

//---ROM,RAMC,RAMD---------------------------------------------------------------------------------;
/***
*  ROM,RAMC,RAMD control
**/

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t ECCCS;
  __IO  uint32_t ECCADR;
  __IO  uint32_t ECCDATA;
  __IO  uint32_t ECCECC;
  __IO  uint32_t TEST_TUNING;
} MEMControl;

#define ROM_CNTR_BASE             (PERIPH_BASE + 0x05000)
#define RAM_CNTR_BASE             (PERIPH_BASE + 0x08000)

#define RAMC1_CNTR_BASE           (RAM_CNTR_BASE + 0x0000)
#define RAMC2_CNTR_BASE           (RAM_CNTR_BASE + 0x1000)
#define RAMD1_CNTR_BASE           (RAM_CNTR_BASE + 0x2000)
#define RAMD2_CNTR_BASE           (RAM_CNTR_BASE + 0x3000)

#define ROM_CNTR                  ((MEMControl *) ROM_CNTR_BASE)
#define RAMC1_CNTR                ((MEMControl *) RAMC1_CNTR_BASE)
#define RAMC2_CNTR                ((MEMControl *) RAMC2_CNTR_BASE)
#define RAMD1_CNTR                ((MEMControl *) RAMD1_CNTR_BASE)
#define RAMD2_CNTR                ((MEMControl *) RAMD2_CNTR_BASE)

#define RCACHE_BASE               (( uint32_t) 0x4000b000)
#define RCACHE                    ((CacheControl *) RCACHE_BASE)

//---EXTBUS----------------------------------------------------------------------------------------;
/***
*  EXTBUS control
**/
typedef struct
{
  __IO  uint32_t RGN0_CNTRL;
  __IO  uint32_t RGN0_ECCBASE;
  __IO  uint32_t RGN0_ECCS;
  __IO  uint32_t RGN0_STATE;

  __IO  uint32_t RGN1_CNTRL;
  __IO  uint32_t RGN1_ECCBASE;
  __IO  uint32_t RGN1_ECCS;
  __IO  uint32_t RGN1_STATE;

  __IO  uint32_t RGN2_CNTRL;
  __IO  uint32_t RGN2_ECCBASE;
  __IO  uint32_t RGN2_ECCS;
  __IO  uint32_t RGN2_STATE;

  __IO  uint32_t RGN3_CNTRL;
  __IO  uint32_t RGN3_ECCBASE;
  __IO  uint32_t RGN3_ECCS;
  __IO  uint32_t RGN3_STATE;

  __IO  uint32_t RGN4_CNTRL;
  __IO  uint32_t RGN4_ECCBASE;
  __IO  uint32_t RGN4_ECCS;
  __IO  uint32_t RGN4_STATE;

  __IO  uint32_t RGN5_CNTRL;
  __IO  uint32_t RGN5_ECCBASE;
  __IO  uint32_t RGN5_ECCS;
  __IO  uint32_t RGN5_STATE;

  __IO  uint32_t RGN6_CNTRL;
  __IO  uint32_t RGN6_ECCBASE;
  __IO  uint32_t RGN6_ECCS;
  __IO  uint32_t RGN6_STATE;

  __IO  uint32_t RGN7_CNTRL;
  __IO  uint32_t RGN7_ECCBASE;
  __IO  uint32_t RGN7_ECCS;
  __IO  uint32_t RGN7_STATE;

  __IO  uint32_t KEY;
  __IO  uint32_t ECC_ADDR;
  __IO  uint32_t ECC_DATA;
  __IO  uint32_t ECC_ECC;
  __IO  uint32_t OCLK;
} EXTBUSControl;

#define EXT_BUS_CNTR_BASE         (PERIPH_BASE + 0x0C000)

#define EXT_BUS_CNTR              ((EXTBUSControl *) EXT_BUS_CNTR_BASE)

#define EB_CNTR_MODE(mode)        ((mode & 3) << 4)
#define EB_CNTR_ECCMODE           4
#define EB_CNTR_ECCEN             2
#define EB_CNTR_EN                1
#define EB_CNTR_WS_HOLD(hold)     ((hold & 0xf) << 20)
#define EB_CNTR_WS_ACTIVE(act)    ((act & 0xf) << 16)
#define EB_CNTR_WS_SETUP(setup)   ((setup & 0xff) << 8)

//---PORT------------------------------------------------------------------------------------------;
/***
*  PORT control
**/

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t RXTX;
  __IO  uint32_t SRXTX;
  __IO  uint32_t CRXTX;

  __IO  uint32_t SOE;
  __IO  uint32_t COE;

  __IO  uint32_t SFUNC[4];

  __IO  uint32_t CFUNC[4];

  __IO  uint32_t SANALOG;
  __IO  uint32_t CANALOG;

  __IO  uint32_t SPULLUP;
  __IO  uint32_t CPULLUP;

  __IO  uint32_t SPULLDOWN;
  __IO  uint32_t CPULLDOWN;

  __IO  uint32_t SPD;
  __IO  uint32_t CPD;

  __IO  uint32_t SPWR[2];
  __IO  uint32_t CPWR[2];

  __IO  uint32_t SCL;
  __IO  uint32_t CCL;

  __IO  uint32_t SIE;
  __IO  uint32_t CIE;

  __IO  uint32_t SIT;
  __IO  uint32_t CIT;

  __IO  uint32_t SIR;
  __IO  uint32_t CIR;

  __IO  uint32_t HCUR;
} PortControl;

#define MDR_PORT_BASE             (PERIPH_BASE + 0x80000)

#define PORTA_BASE                (MDR_PORT_BASE + 0x0000)
#define PORTB_BASE                (MDR_PORT_BASE + 0x1000)
#define PORTC_BASE                (MDR_PORT_BASE + 0x2000)
#define PORTD_BASE                (MDR_PORT_BASE + 0x3000)
#define PORTE_BASE                (MDR_PORT_BASE + 0x4000)
#define PORTF_BASE                (MDR_PORT_BASE + 0x5000)

#define PORTA                     ((PortControl *) PORTA_BASE)
#define PORTB                     ((PortControl *) PORTB_BASE)
#define PORTC                     ((PortControl *) PORTC_BASE)
#define PORTD                     ((PortControl *) PORTD_BASE)
#define PORTE                     ((PortControl *) PORTE_BASE)
#define PORTF                     ((PortControl *) PORTF_BASE)

#define FUNC_MASK 0x0f
#define FUNCREGNUM(pin) (pin >> 3)
#define _FUNCPIN(TYPE) TYPE ## FUNC
#define FUNCPIN(pin,TYPE) _FUNCPIN(TYPE)[FUNCREGNUM(pin)]
#define SFUNCPIN(pin) FUNCPIN(pin,S)
#define CFUNCPIN(pin) FUNCPIN(pin,C)
#define FUNCVAL(pin,func) ((func & FUNC_MASK) << ((pin % 8)<<2))

#define PWR_MASK 0x3
#define PWRREGNUM(pin) (pin >> 4)
#define _PWRPIN(type) type ## PWR
#define PWRPIN(pin, type) _PWRPIN(type)[PWRREGNUM(pin)]
#define SPWRPIN(pin) PWRPIN(pin, S)
#define CPWRPIN(pin) PWRPIN(pin, C)
#define PWRVAL(pin, pwr) ((pwr & PWR_MASK) << ((pin % 16) << 1))

// //---CANFD--------------------------------------------------------------------------------------;
/***
*  MDR_CANFD control
**/
typedef struct
{
  __IO    uint32_t CTRL[3];
}MDR_CANFD_TXCTRL_TypeDef;

typedef struct
{
  // Control registers
  __IO  uint32_t CONTROL;
  __IO  uint32_t CFG0;
  __IO  uint32_t CFG1;
  __IO  uint32_t CFG2;
  __IO  uint32_t CFG3;
  // Filter config register
  __IO  uint32_t RXFCFG;
  // Prescalers
  __IO  uint32_t PRSC;
  __IO  uint32_t FPRSC;
  // IRQ resiters
  __I   uint32_t ST;
  __IO  uint32_t MSK;
  // Rx queue Base Addr
  __IO  uint32_t RXBADDR;
  // Tx queue Base Addr
  __IO  uint32_t TXBADDR[4];
  // Timer register
  __I   uint32_t CURTIMEHi;
  __I   uint32_t CURTIMELo;
        uint32_t Reserved1[3];

  // Rx Queue Control register
  __IO  uint32_t RXQCTRL[2];
  // Tx Queue Control register (Set)
  MDR_CANFD_TXCTRL_TypeDef TXQCTRL[4];
  // Tx Queue Control register (Clear)
  MDR_CANFD_TXCTRL_TypeDef TXRCTRL[4];
        uint32_t Reserved2[2];

  // Filtration pattern
  __IO  uint32_t RXF[16];
  // Filtration mask
  __IO  uint32_t RXFMSK[16];

  // Error Counter registers
  __I   uint32_t TECE;
  __I   uint32_t RECE;
  __I   uint32_t TEC;
  __I   uint32_t REC;
  __I   uint32_t EOVLC;
  __I   uint32_t EPSC;
  __I   uint32_t BOSC;
  __I   uint32_t LMSGLC;
}MDR_CANFD_TypeDef;

#define MDR_CANFD_BASE            (PERIPH_BASE + 0x80000)

#define MDR_CANFD0_BASE           (MDR_CANFD_BASE + 0x6000)

#define MDR_CANFD0                ((MDR_CANFD_TypeDef *) MDR_CANFD0_BASE)

//---SSP-------------------------------------------------------------------------------------------;
/***
*  MDR_SSP control
**/
typedef struct
{
  __IO  uint32_t CR0;
  __IO  uint32_t CR1;
  __IO  uint32_t DR;
  __IO  uint32_t SR;
  __IO  uint32_t CPSR;
  __IO  uint32_t IMSC;
  __IO  uint32_t RIS;
  __IO  uint32_t MIS;
  __IO  uint32_t ICR;
  __IO  uint32_t DMACR;
}MDR_SSP_TypeDef;

#define MDR_SSP_BASE              (PERIPH_BASE + 0x80000)

#define MDR_SSP0_BASE             (MDR_SSP_BASE + 0x9000)
#define MDR_SSP1_BASE             (MDR_SSP_BASE + 0xA000)

#define MDR_SSP0                  ((MDR_SSP_TypeDef *) MDR_SSP0_BASE)
#define MDR_SSP1                  ((MDR_SSP_TypeDef *) MDR_SSP1_BASE)

//---CAN-------------------------------------------------------------------------------------------;
/***
*  MDR_CAN control
**/
typedef struct
{
  __IO  uint32_t ID;
  __IO  uint32_t DLC;
  __IO  uint32_t DATAL;
  __IO  uint32_t DATAH;
}MDR_CAN_BUF_TypeDef;

typedef struct
{
  __IO  uint32_t MASK;
  __IO  uint32_t FILTER;
}MDR_CAN_BUF_FILTER_TypeDef;

typedef struct
{
  __IO  uint32_t CONTROL;
  __IO  uint32_t STATUS;
  __IO  uint32_t BITTMNG;
  __IO  uint32_t Reserved0;
  __IO  uint32_t INT_EN;
  __IO  uint32_t Reserved1[2];
  __IO  uint32_t OVER;
  __IO  uint32_t RXID;
  __IO  uint32_t RXDLC;
  __IO  uint32_t RXDATAL;
  __IO  uint32_t RXDATAH;
  __IO  uint32_t TXID;
  __IO  uint32_t TXDLC;
  __IO  uint32_t DATAL;
  __IO  uint32_t DATAH;
  __IO  uint32_t BUF_CON[32];
  __IO  uint32_t INT_RX;
  __IO  uint32_t RX;
  __IO  uint32_t INT_TX;
  __IO  uint32_t TX;
  __IO  uint32_t Reserved2[76];
  MDR_CAN_BUF_TypeDef BUF[32];
  __IO  uint32_t Reserved3[64];
  MDR_CAN_BUF_FILTER_TypeDef FILTER[32];
}MDR_CAN_TypeDef;

#define MDR_CAN_BASE              (PERIPH_BASE + 0x80000)

#define MDR_CAN0_BASE             (MDR_CAN_BASE + 0xB000)
#define MDR_CAN1_BASE             (MDR_CAN_BASE + 0xC000)

#define MDR_CAN0                  ((MDR_CAN_TypeDef *) MDR_CAN0_BASE)
#define MDR_CAN1                  ((MDR_CAN_TypeDef *) MDR_CAN1_BASE)

//---UART------------------------------------------------------------------------------------------;
/***
*  MDR_UART control
**/
typedef struct
{
  __IO  uint32_t DR;
  __IO  uint32_t RSR_ECR;
  __IO  uint32_t Reserved1[4];
  __IO  uint32_t FR;
  __IO  uint32_t Reserved2;
  __IO  uint32_t ILPR;
  __IO  uint32_t IBRD;
  __IO  uint32_t FBRD;
  __IO  uint32_t LCR_H;
  __IO  uint32_t CR;
  __IO  uint32_t IFLS;
  __IO  uint32_t IMSC;
  __IO  uint32_t RIS;
  __IO  uint32_t MIS;
  __IO  uint32_t ICR;
  __IO  uint32_t DMACR;
}MDR_UART_TypeDef;

#define MDR_UART_BASE             (PERIPH_BASE   + 0x80000)

#define MDR_UART0_BASE            (MDR_UART_BASE + 0x0D000)
#define MDR_UART1_BASE            (MDR_UART_BASE + 0x0E000)
#define MDR_UART2_BASE            (MDR_UART_BASE + 0x0F000)
#define MDR_UART3_BASE            (MDR_UART_BASE + 0x10000)

#define MDR_UART0                 ((MDR_UART_TypeDef *) MDR_UART0_BASE)
#define MDR_UART1                 ((MDR_UART_TypeDef *) MDR_UART1_BASE)
#define MDR_UART2                 ((MDR_UART_TypeDef *) MDR_UART2_BASE)
#define MDR_UART3                 ((MDR_UART_TypeDef *) MDR_UART3_BASE)

//---MIL-------------------------------------------------------------------------------------------;
/***
*   MIL1553 Control
**/

typedef struct
{
  __IO  uint32_t CONTROL;
  __IO  uint32_t STATUS;
  __IO  uint32_t ERROR;
  __IO  uint32_t CommandWord1;
  __IO  uint32_t CommandWord2;
  __IO  uint32_t ModeData;
  __IO  uint32_t StatusWord1;
  __IO  uint32_t StatusWord2;
  __IO  uint32_t INTEN;
  __IO  uint32_t MSG;
  __IO  uint32_t RESERVED[1014];
  __IO  uint32_t DATA[1024];
} MIL1553Control;

#define MIL0_15531_BASE             (PERIPH_BASE + 0x90000 + 0x1000)
#define MIL1_15531_BASE             (PERIPH_BASE + 0x80000 + 0x7000)

#define MIL0_STD_15531             ((MIL1553Control *) MIL0_15531_BASE)
#define MIL1_STD_15531             ((MIL1553Control *) MIL1_15531_BASE)

//---USB_RAM---------------------------------------------------------------------------------------;
/****
/ USB_RAM interface
**/

typedef struct
{
  /* Common USB registers */
  __IO uint32_t  USB_RAM_CNTR;
  __IO uint32_t  USB_M31_CNTR;
}
USBRAM_Typedef;

#define MDR_USB_RAM_BASE          (PERIPH_BASE      + 0x90000)

#define MDR_USB_RAM0_BASE         (MDR_USB_RAM_BASE + 0x03000)

#define MDR_USB_RAM0              ((USBRAM_Typedef *) MDR_USB_RAM0_BASE)

//---TMR-------------------------------------------------------------------------------------------;
/***
*  TIMER32 control
**/
typedef struct
{
  __IO  uint32_t CNT;
  __IO  uint32_t PSG;
  __IO  uint32_t ARR;
  __IO  uint32_t CNTRL;
  __IO  uint32_t CCR1;
  __IO  uint32_t CCR2;
  __IO  uint32_t CCR3;
  __IO  uint32_t CCR4;
  __IO  uint32_t CH1_CNTRL;
  __IO  uint32_t CH2_CNTRL;
  __IO  uint32_t CH3_CNTRL;
  __IO  uint32_t CH4_CNTRL;
  __IO  uint32_t CH1_CNTRL1;
  __IO  uint32_t CH2_CNTRL1;
  __IO  uint32_t CH3_CNTRL1;
  __IO  uint32_t CH4_CNTRL1;
  __IO  uint32_t CH1_DTG;
  __IO  uint32_t CH2_DTG;
  __IO  uint32_t CH3_DTG;
  __IO  uint32_t CH4_DTG;
  __IO  uint32_t BRKETR_CNTRL;
  __IO  uint32_t STATUS;
  __IO  uint32_t IE;
  __IO  uint32_t DMA_RE;
  __IO  uint32_t CH1_CNTRL2;
  __IO  uint32_t CH2_CNTRL2;
  __IO  uint32_t CH3_CNTRL2;
  __IO  uint32_t CH4_CNTRL2;
  __IO  uint32_t CCR11;
  __IO  uint32_t CCR21;
  __IO  uint32_t CCR31;
  __IO  uint32_t CCR41;
  __IO  uint32_t DMA_RECh1;
  __IO  uint32_t DMA_RECh2;
  __IO  uint32_t DMA_RECh3;
  __IO  uint32_t DMA_RECh4;
}MDR_TMR_TypeDef;

#define MDR_TMR_BASE              (PERIPH_BASE + 0x90000)

#define MDR_TMR0_BASE             (MDR_TMR_BASE + 0x4000)
#define MDR_TMR1_BASE             (MDR_TMR_BASE + 0x5000)
#define MDR_TMR2_BASE             (MDR_TMR_BASE + 0x6000)
#define MDR_TMR3_BASE             (MDR_TMR_BASE + 0x7000)

#define MDR_TMR0                  ((MDR_TMR_TypeDef *) MDR_TMR0_BASE)
#define MDR_TMR1                  ((MDR_TMR_TypeDef *) MDR_TMR1_BASE)
#define MDR_TMR2                  ((MDR_TMR_TypeDef *) MDR_TMR2_BASE)
#define MDR_TMR3                  ((MDR_TMR_TypeDef *) MDR_TMR3_BASE)

//---CAP-------------------------------------------------------------------------------------------;
/***
*  CAPx control
**/

typedef struct
{
  __IO  uint32_t TSCTR;
  __IO  uint32_t CTRPHS;
  __IO  uint32_t CAP1;
  __IO  uint32_t CAP2;
  __IO  uint32_t CAP3;
  __IO  uint32_t CAP4;
  __IO  uint32_t ECCTL1;
  __IO  uint32_t ECCTL2;
  __IO  uint32_t ECEINT;
  __IO  uint32_t ECFLG;
  __IO  uint32_t ECCLR;
  __IO  uint32_t ECFRC;
} CAPControl;

#define MDR_CAP_BASE              (PERIPH_BASE + 0x90000)

#define CAP0_BASE                 (MDR_CAP_BASE + 0x8000)
#define CAP1_BASE                 (MDR_CAP_BASE + 0x9000)
#define CAP2_BASE                 (MDR_CAP_BASE + 0xA000)
#define CAP3_BASE                 (MDR_CAP_BASE + 0xB000)

#define MDR_CAP0                  ((CAPControl  *) CAP0_BASE)
#define MDR_CAP1                  ((CAPControl  *) CAP1_BASE)
#define MDR_CAP2                  ((CAPControl  *) CAP2_BASE)
#define MDR_CAP3                  ((CAPControl  *) CAP3_BASE)

//---QEP-------------------------------------------------------------------------------------------;
/***
*  QEPx control
**/

typedef struct
{
  __IO  uint32_t QDECCTL;
  __IO  uint32_t QEPCTL;
  __IO  uint32_t QPOSCTL;
  __IO  uint32_t QCAPCTL;
  __IO  uint32_t QPOSCNT;
  __IO  uint32_t QPOSINIT;
  __IO  uint32_t QPOSMAX;
  __IO  uint32_t QPOSCMP;
  __IO  uint32_t QPOSILAT;
  __IO  uint32_t QPOSSLAT;
  __IO  uint32_t QPOSLAT;
  __IO  uint32_t QUTMR;
  __IO  uint32_t QUPRD;
  __IO  uint32_t QWDTMR;
  __IO  uint32_t QEINT;
  __IO  uint32_t QFLG;
  __IO  uint32_t QCLR;
  __IO  uint32_t QFRC;
  __IO  uint32_t QEPSTS;
  __IO  uint32_t QWDPRD;
  __IO  uint32_t QCTMR;
  __IO  uint32_t QCTMR1;
  __IO  uint32_t QCTMR2;
  __IO  uint32_t QCTMR3;
  __IO  uint32_t QCTMR4;
  __IO  uint32_t QCPRD;
  __IO  uint32_t QCTMRLAT;
  __IO  uint32_t QCPRDLAT;
} QEPControl;

#define MDR_QEP_BASE              (PERIPH_BASE + 0x90000)

#define QEP0_BASE                 (MDR_QEP_BASE + 0xC000)
#define QEP1_BASE                 (MDR_QEP_BASE + 0xD000)

#define QEP0                      ((QEPControl  *) QEP0_BASE)
#define QEP1                      ((QEPControl  *) QEP1_BASE)

//---PWM-------------------------------------------------------------------------------------------;
/***
*  PWMx control
**/

typedef struct
{
  __IO  uint32_t TBPRD;
  uint32_t RESERVED0;
  __IO  uint32_t TBPHS;
  __IO  uint32_t TBCTR;
  __IO  uint32_t TBCTL;
  __IO  uint32_t TBSTS;
  __IO  uint32_t CMPA;
  __IO  uint32_t CMPB;
  __IO  uint32_t CMPCTL;
  uint32_t RESERVED1;
  __IO  uint32_t AQCTLA;
  __IO  uint32_t AQCTLB;
  __IO  uint32_t AQSFRC;
  __IO  uint32_t AQCSFRC;
  __IO  uint32_t DBCTL;
  __IO  uint32_t DBRED;
  __IO  uint32_t DBFED;
  __IO  uint32_t PCCTL;
  __IO  uint32_t TZSEL;
  __IO  uint32_t TZCTL;
  __IO  uint32_t TZEINT;
  __IO  uint32_t TZFLG;
  __IO  uint32_t TZCLR;
  __IO  uint32_t TZFRC;
  __IO  uint32_t ETSEL;
  __IO  uint32_t ETPS;
  __IO  uint32_t ETFLG;
  __IO  uint32_t ETCLR;
  __IO  uint32_t ETFRC;
  uint32_t RESERVED2;
  uint32_t RESERVED3;
  __IO  uint32_t HRPWM_CTRL;
  
} PWMControl;

#define MDR_PWM_BASE              (PERIPH_BASE +  0x9E000)

#define PWM0_BASE                 (MDR_PWM_BASE + 0x00000)
#define PWM1_BASE                 (MDR_PWM_BASE + 0x01000)
#define PWM2_BASE                 (MDR_PWM_BASE + 0x02000)
#define PWM3_BASE                 (MDR_PWM_BASE + 0x03000)
#define PWM4_BASE                 (MDR_PWM_BASE + 0x04000)
#define PWM5_BASE                 (MDR_PWM_BASE + 0x05000)
#define PWM6_BASE                 (MDR_PWM_BASE + 0x06000)
#define PWM7_BASE                 (MDR_PWM_BASE + 0x07000)
#define PWM8_BASE                 (MDR_PWM_BASE + 0x08000)

#define PWM0                      ((PWMControl  *) PWM0_BASE)
#define PWM1                      ((PWMControl  *) PWM1_BASE)
#define PWM2                      ((PWMControl  *) PWM2_BASE)
#define PWM3                      ((PWMControl  *) PWM3_BASE)
#define PWM4                      ((PWMControl  *) PWM4_BASE)
#define PWM5                      ((PWMControl  *) PWM5_BASE)
#define PWM6                      ((PWMControl  *) PWM6_BASE)
#define PWM7                      ((PWMControl  *) PWM7_BASE)
#define PWM8                      ((PWMControl  *) PWM8_BASE)

//---ADC-------------------------------------------------------------------------------------------;
/***
*  ADCx control
**/

typedef struct
{
  __IO  uint32_t ADC0CTRL;
  __IO  uint32_t ADC1CTRL;
  __IO  uint32_t ADC0SCOPECTRL;
  __IO  uint32_t ADC1SCOPECTRL;
  __IO  uint32_t ADCSYNCCTRL;
  __IO  uint32_t BUF_MODE_ADC;
  __IO  uint32_t BUF_STATE;
  __IO  uint32_t INT_CTRL_ADC;
  __IO  uint32_t DMARQ_CTRL_ADC;
    uint32_t Reserved0;
  __IO  uint32_t ANALOG_CTRL;
  __IO  uint32_t BNGP_CTRL;
  uint32_t Reserved1[4];
  __IO  uint32_t ADC0_CHNL_SEL[8];
  __IO  uint32_t ADC1_CHNL_SEL[8];
  __IO  uint32_t ADC0_RESULT[32];
  __IO  uint32_t ADC1_RESULT[32];
} ADCxControl;

#define MDR_ADC_BASE              (PERIPH_BASE + 0xA0000)

#define ADC0_BASE                 (MDR_ADC_BASE + 0x7000)
#define ADC1_BASE                 (MDR_ADC_BASE + 0x8000)
#define ADC2_BASE                 (MDR_ADC_BASE + 0x9000)

#define ADC0                      ((ADCxControl *) ADC0_BASE)
#define ADC1                      ((ADCxControl *) ADC1_BASE)
#define ADC2                      ((ADCxControl *) ADC2_BASE)

//---DAC-------------------------------------------------------------------------------------------;
/***
*  DACx control
**/

typedef struct
{
  __IO  uint32_t CTRL;
  __IO  uint32_t FIFO_CTRL;
  __IO  uint32_t PRD;
  __IO  uint32_t CNT;

  __IO  uint32_t IE;
  __IO  uint32_t RE;
  __IO  uint32_t INT;
  __IO  uint32_t DATA;
} DACxControl;

#define MDR_DAC_BASE              (PERIPH_BASE + 0xA0000)

#define DAC0_BASE                 (MDR_DAC_BASE + 0xA000)
#define DAC1_BASE                 (MDR_DAC_BASE + 0xB000)
#define DAC2_BASE                 (MDR_DAC_BASE + 0xC000)
#define DAC3_BASE                 (MDR_DAC_BASE + 0xD000)

#define DAC0                      ((DACxControl *) DAC0_BASE)
#define DAC1                      ((DACxControl *) DAC1_BASE)
#define DAC2                      ((DACxControl *) DAC2_BASE)
#define DAC3                      ((DACxControl *) DAC3_BASE)

//---COMP------------------------------------------------------------------------------------------;
/***
*  COMP control
**/

typedef struct
{
  __IO  uint32_t COMP_CNTR;
  __IO  uint32_t COMP_EVNT;
  __IO  uint32_t ANABG_CTRL;
} CompControl;

#define MDR_COMP_BASE             (PERIPH_BASE + 0xA0000)

#define COMP0_BASE                (MDR_COMP_BASE + 0x0E000)
#define COMP1_BASE                (MDR_COMP_BASE + 0x0F000)
#define COMP2_BASE                (MDR_COMP_BASE + 0x10000)
#define COMP3_BASE                (MDR_COMP_BASE + 0x11000)

#define COMP0                     ((CompControl *) COMP0_BASE)
#define COMP1                     ((CompControl *) COMP1_BASE)
#define COMP2                     ((CompControl *) COMP2_BASE)
#define COMP3                     ((CompControl *) COMP3_BASE)

//---I2C-------------------------------------------------------------------------------------------;
/***
*  MDR_I2C control
**/
typedef struct
{
  __IO  uint32_t PRL;
  __IO  uint32_t PRH;
  __IO  uint32_t CTR;
  __IO  uint32_t RXD;
  __IO  uint32_t STA;
  __IO  uint32_t TXD;
  __IO  uint32_t CMD;
}MDR_I2C_TypeDef;

#define MDR_I2C_BASE              (PERIPH_BASE   + 0xB2000)

#define MDR_I2C                   ((MDR_I2C_TypeDef *) MDR_I2C_BASE)

//---ORDIC-----------------------------------------------------------------------------------------;
/***
*  CORDICx control
**/

typedef struct
{
  __IO  uint32_t CTRL;
  __IO  uint32_t STATUS;
  __IO  uint32_t INTF;
  __IO  uint32_t INTE;
  __IO  uint32_t IN_X;
  __IO  uint32_t IN_Y;
  __IO  uint32_t IN_A;
  __IO  uint32_t IN_SEQ;
  __IO  uint32_t OUT_X;
  __IO  uint32_t OUT_Y;
  __IO  uint32_t OUT_A;
  __IO  uint32_t OUT_SEQ;
  __IO  uint32_t IN_ADDR;
  __IO  uint32_t OUT_ADDR;
} CRDControl;

#define MDR_CRD_BASE              (PERIPH_BASE + 0xB0000)

#define CRD0_BASE                 (MDR_CRD_BASE + 0x3000)

#define MDR_CRDC                  ((CRDControl  *) CRD0_BASE)


/*
 * ==========================================================================
 * -------------------------- Gate ------------------------------------------
 * ==========================================================================
 */
typedef struct
{
    __IO uint32_t OP_FIFO_OP_TO_SF;
    __IO uint32_t OP_FIFO_SF_TO_OP;
    __IO uint32_t OP_FIFO_LEVELS;
    __IO uint32_t OP_FIFO_INT_MASK;
    __IO uint32_t OP_FIFO_INT_SOURCE;
    __IO uint32_t OP_REG[16];
    __IO uint32_t OP_REGS_BUSY;
    __IO uint32_t OP_REGS_INT_MASK;
    __IO uint32_t OP_REGS_INT_SOURCE;
} GateRegs;

#define GATE_BASE             ((uint32_t)0x21030000)       
#define GATE_REGS             ((GateRegs *)GATE_BASE)

#endif
