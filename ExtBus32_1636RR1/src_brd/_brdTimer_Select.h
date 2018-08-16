#ifndef _BRD_TIMER_SELECT_H
#define _BRD_TIMER_SELECT_H

#include "brdTimer.h"

//  Pattern for timer counter
Timer_Obj brdTimer1 =
{
  .TIMERx     = MDR_TIMER1,             //  MDR_TIMER_TypeDef*  TIMERx;
  .ClockMask  = RST_CLK_PCLK_TIMER1,    //  uint32_t    ClockMask;
  .ClockBRG   = TIMER_HCLKdiv1,         //  uint32_t    ClockBRG;
  .EventIT    = TIMER_STATUS_CNT_ARR,   //  uint32_t    EventIT;
  .IRQn       = Timer1_IRQn             //  IRQn_Type   IRQn;  
};

//  Pattern for Capture timer pin
PORT_InitTypeDef pinTimerCAP =
{
  .PORT_Pin       = 0,
  .PORT_OE        = PORT_OE_IN,
  .PORT_PULL_UP   = PORT_PULL_UP_OFF,
  .PORT_PULL_DOWN = PORT_PULL_DOWN_ON, //PORT_PULL_DOWN_OFF,
  .PORT_PD_SHM    = PORT_PD_SHM_OFF,
  .PORT_PD        = PORT_PD_DRIVER,
  .PORT_GFEN      = PORT_GFEN_OFF,
  .PORT_FUNC      = PORT_FUNC_MAIN,
  .PORT_SPEED     = PORT_SPEED_MAXFAST,
  .PORT_MODE      = PORT_MODE_DIGITAL
};

//  Pattern for WPM timer pin
PORT_InitTypeDef pinTimerPWM =
{
  .PORT_Pin       = 0,
  .PORT_OE        = PORT_OE_OUT,
  .PORT_PULL_UP   = PORT_PULL_UP_OFF,
  .PORT_PULL_DOWN = PORT_PULL_DOWN_OFF,
  .PORT_PD_SHM    = PORT_PD_SHM_OFF,
  .PORT_PD        = PORT_PD_DRIVER,
  .PORT_GFEN      = PORT_GFEN_OFF,
  .PORT_FUNC      = PORT_FUNC_MAIN,
  .PORT_SPEED     = PORT_SPEED_MAXFAST,
  .PORT_MODE      = PORT_MODE_DIGITAL
};



#endif //_BRD_TIMER_SELECT_H
