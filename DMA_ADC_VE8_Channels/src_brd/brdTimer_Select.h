#ifndef _BRD_TIMER_SELECT_H
#define _BRD_TIMER_SELECT_H

//#include <MDR32F9Qx_port.h>
//#include <MDR32F9Qx_rst_clk.h>
//#include <MDR32F9Qx_timer.h>

//#include <stdint.h>

#include "brdTimer.h"

#ifdef USE_BOARD_VE_1
  #define Timer1_IRQn   TIMER1_IRQn
#endif

Timer_Obj brdTimer1 =
{
  MDR_TIMER1,             //  MDR_TIMER_TypeDef*  TIMERx;
  RST_CLK_PCLK_TIMER1,    //  uint32_t    ClockMask;
  TIMER_HCLKdiv1,         //  uint32_t    ClockBRG;
  TIMER_STATUS_CNT_ARR,   //  uint32_t    EventIT;
  Timer1_IRQn             //  IRQn_Type   IRQn;
};



#endif //_BRD_TIMER_SELECT_H
