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

//// Обработчик аппаратных прерываний от таймера TIMER1
//void Timer1_IRQHandler (void)
//{
//  // Сброс прерывания от таймера TIMER1
//  TIMER_ClearITPendingBit (MDR_TIMER1, TIMER_STATUS_CNT_ARR);
//}
