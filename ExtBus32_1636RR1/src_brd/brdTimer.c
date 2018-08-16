#include <math.h>

#include "brdTimer.h"

void BRD_Timer_InitStructDef(TIMER_CntInitTypeDef *TimerInitStruct, uint32_t freq, uint32_t rangeCNT)
{
  uint32_t presc = ceil((double) BRD_CPU_CLK / (rangeCNT * freq));
    
  TIMER_CntStructInit (TimerInitStruct);
  TimerInitStruct->TIMER_Prescaler        = presc - 1;                          // Предделитель частоты
  TimerInitStruct->TIMER_Period           = BRD_CPU_CLK / (presc * freq) - 1;   // Период таймера, (при -1 точнее выводится частоты сигнала в DAC по DMA)
}

void BRD_Timer_Init(Timer_Obj *TimerObj, TIMER_CntInitTypeDef *TimerInitStruct)
{
  // Включение тактирования таймера
  RST_CLK_PCLKcmd (TimerObj->ClockMask, ENABLE);

  // Деинициализация таймера
  TIMER_DeInit (TimerObj->TIMERx);

  // Выбор предделителя тактовой частоты таймера 
  TIMER_BRGInit (TimerObj->TIMERx, TimerObj->ClockBRG);

 // Инициализация таймера
  TIMER_CntInit (TimerObj->TIMERx, TimerInitStruct);
}

void BRD_Timer_Start(Timer_Obj *TimerObj)
{
  TIMER_Cmd (TimerObj->TIMERx, ENABLE);
}

void BRD_Timer_InitIRQ(Timer_Obj *TimerObj, uint32_t priority)
{
  // Выбор источников прерываний
  TIMER_ITConfig (TimerObj->TIMERx, TimerObj->EventIT, ENABLE);
  
  // Назначение приоритета аппаратных прерываний от таймера
  NVIC_SetPriority (TimerObj->IRQn, 1);

  // Включение аппаратных прерываний от таймера 
  NVIC_EnableIRQ (TimerObj->IRQn);
}

void BRD_TimerChannel_InitStructPWM(uint16_t channel, TIMER_ChnInitTypeDef* pChanCfg, TIMER_ChnOutInitTypeDef* pChanOutCfg)
{
  //  PWM channel
  pChanCfg->TIMER_CH_Number           = channel;
  pChanCfg->TIMER_CH_Mode             = TIMER_CH_MODE_PWM;
  pChanCfg->TIMER_CH_REF_Format       = TIMER_CH_REF_Format6;  
  
  //  Rest of
  pChanCfg->TIMER_CH_FilterConf       = TIMER_Filter_1FF_at_TIMER_CLK;
  pChanCfg->TIMER_CH_CCR_UpdateMode   = TIMER_CH_CCR_Update_Immediately;  
  pChanCfg->TIMER_CH_EventSource      = TIMER_CH_EvSrc_PE;  
  pChanCfg->TIMER_CH_CCR1_Ena         = DISABLE;
  pChanCfg->TIMER_CH_CCR1_EventSource = TIMER_CH_CCR1EvSrc_NE;  
  pChanCfg->TIMER_CH_ETR_Ena          = DISABLE;
  pChanCfg->TIMER_CH_ETR_Reset        = TIMER_CH_ETR_RESET_Disable;
  pChanCfg->TIMER_CH_BRK_Reset        = TIMER_CH_BRK_RESET_Disable;
  pChanCfg->TIMER_CH_Prescaler        = TIMER_CH_Prescaler_None;  
  
  
  // Channel output pins
  pChanOutCfg->TIMER_CH_Number            = channel;  
  pChanOutCfg->TIMER_CH_DirOut_Source     = TIMER_CH_OutSrc_REF;          //  Ref signal
  pChanOutCfg->TIMER_CH_DirOut_Mode       = TIMER_CH_OutMode_Output;      //  Output
  pChanOutCfg->TIMER_CH_DirOut_Polarity   = TIMER_CHOPolarity_NonInverted;  
  
  pChanOutCfg->TIMER_CH_NegOut_Source     = TIMER_CH_OutSrc_Only_0;
  pChanOutCfg->TIMER_CH_NegOut_Mode       = TIMER_CH_OutMode_Input;
  pChanOutCfg->TIMER_CH_NegOut_Polarity   = TIMER_CHOPolarity_NonInverted;
  
  pChanOutCfg->TIMER_CH_DTG_MainPrescaler = 0;
  pChanOutCfg->TIMER_CH_DTG_AuxPrescaler  = 0;
  pChanOutCfg->TIMER_CH_DTG_ClockSource   = TIMER_CH_DTG_ClkSrc_TIMER_CLK;
}  

void BRD_TimerChannel_InitStructCAP(uint16_t channel, TIMER_ChnInitTypeDef* pChanCfg, TIMER_ChnOutInitTypeDef* pChanOutCfg)
{
  //  Capture channel
  pChanCfg->TIMER_CH_Number           = channel;
  pChanCfg->TIMER_CH_Mode             = TIMER_CH_MODE_CAPTURE;
  pChanCfg->TIMER_CH_FilterConf       = TIMER_Filter_1FF_at_TIMER_CLK;
  pChanCfg->TIMER_CH_CCR_UpdateMode   = TIMER_CH_CCR_Update_Immediately;
  
  pChanCfg->TIMER_CH_EventSource      = TIMER_CH_EvSrc_PE;  
  pChanCfg->TIMER_CH_CCR1_Ena         = DISABLE;
  pChanCfg->TIMER_CH_CCR1_EventSource = TIMER_CH_CCR1EvSrc_NE;  
  
  //  Rest of capture
  pChanCfg->TIMER_CH_ETR_Ena          = DISABLE;
  pChanCfg->TIMER_CH_ETR_Reset        = TIMER_CH_ETR_RESET_Disable;
  pChanCfg->TIMER_CH_BRK_Reset        = TIMER_CH_BRK_RESET_Disable;
  pChanCfg->TIMER_CH_REF_Format       = TIMER_CH_REF_Format0;
  pChanCfg->TIMER_CH_Prescaler        = TIMER_CH_Prescaler_None;
  
  
  // Channel output pins
  pChanOutCfg->TIMER_CH_DirOut_Source     = TIMER_CH_OutSrc_Only_0;
  pChanOutCfg->TIMER_CH_DirOut_Mode       = TIMER_CH_OutMode_Input;
  pChanOutCfg->TIMER_CH_DirOut_Polarity   = TIMER_CHOPolarity_NonInverted;

  pChanOutCfg->TIMER_CH_NegOut_Source     = TIMER_CH_OutSrc_Only_0;
  pChanOutCfg->TIMER_CH_NegOut_Mode       = TIMER_CH_OutMode_Input;
  pChanOutCfg->TIMER_CH_NegOut_Polarity   = TIMER_CHOPolarity_NonInverted;  
  
  pChanOutCfg->TIMER_CH_DTG_MainPrescaler = 0;
  pChanOutCfg->TIMER_CH_DTG_AuxPrescaler  = 0;
  pChanOutCfg->TIMER_CH_DTG_ClockSource   = TIMER_CH_DTG_ClkSrc_TIMER_CLK;   
}

void BRD_TimerChannel_Apply(MDR_TIMER_TypeDef* TimerX, TIMER_ChnInitTypeDef* pChanCfg, TIMER_ChnOutInitTypeDef* pChanOutCfg)
{
  // Инициализация канала
  TIMER_ChnInit (TimerX, pChanCfg);
  
  // Инициализация выхода канала
  TIMER_ChnOutInit (TimerX, pChanOutCfg);  
}

//// Обработчик аппаратных прерываний от таймера TIMER1
//void Timer1_IRQHandler (void)
//{
//  // Сброс прерывания от таймера TIMER1
//  TIMER_ClearITPendingBit (MDR_TIMER1, TIMER_STATUS_CNT_ARR);
//}
