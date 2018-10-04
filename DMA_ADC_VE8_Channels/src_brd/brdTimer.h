#ifndef _BRD_TIMER_H
#define _BRD_TIMER_H

#include "brdDef.h"

#ifdef USE_BOARD_VE_8 
  #include  <mdr32f8_clkctrl.h>
  #include  <mdr32f8_tim.h>

  // Timer
  #define MDR_TIMER_TypeDef     MDR_TMR_TypeDef
  #define MDR_TIMER1            MDR_TMR1
  //  Clock
  #define RST_CLK_PCLKcmd       CLKCTRL_PER0_CLKcmd
  #define RST_CLK_PCLK_TIMER1   CLKCTRL_PER0_CLK_MDR_TMR1_EN
  
  //  IT Event
  #define Timer1_IRQn           TMR1_IRQn
  
#else
  #include <MDR32F9Qx_port.h>
  #include <MDR32F9Qx_rst_clk.h>
  #include <MDR32F9Qx_timer.h>
#endif

#include "brdClock.h"

typedef struct
{
  MDR_TIMER_TypeDef*  TIMERx;
  uint32_t            ClockMask;
  uint32_t            ClockBRG;
  uint32_t            EventIT;
  IRQn_Type           IRQn;
  
} Timer_Obj;

void BRD_Timer_InitStructDef(TIMER_CntInitTypeDef *TimerInitStruct, uint32_t freq, uint32_t rangeCNT);
void BRD_Timer_Init(Timer_Obj *TimerObj, TIMER_CntInitTypeDef *TimerInitStruct);
void BRD_Timer_InitIRQ(Timer_Obj *TimerObj, uint32_t priority);
void BRD_Timer_Start(Timer_Obj *TimerObj);

//  Calc Period for output signal by Timer (with DMA)
//  TimerInitStruct->TIMER_Prescaler = 0; 
//  TimerInitStruct->TIMER_Period    = CALC_PERIOD(((SystemCoreClock, 1000, 100); 
#if defined (USE_MDR1986VE3) || defined (USE_MDR1986VE1T)
  #define CALC_PERIOD(Clock, SignalFreq, BuffSize) ((uint32_t)(((Clock) / (uint32_t)((SignalFreq) * (BuffSize))) - 1))
#else
  #define CALC_PERIOD(Clock, SignalFreq, BuffSize) ((uint16_t)(((Clock) / (uint32_t)((SignalFreq) * (BuffSize))) - 1))
#endif

#endif //_BRD_TIMER_H
