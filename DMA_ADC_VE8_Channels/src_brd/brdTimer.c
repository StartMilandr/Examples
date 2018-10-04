#include <math.h>

#include "brdTimer.h"

void BRD_Timer_InitStructDef(TIMER_CntInitTypeDef *TimerInitStruct, uint32_t freq, uint32_t rangeCNT)
{
  uint32_t presc = ceil((double) BRD_CPU_CLK / (rangeCNT * freq));
    
  TIMER_CntStructInit (TimerInitStruct);
  TimerInitStruct->TIMER_Prescaler        = presc - 1;                          // ������������ �������
  TimerInitStruct->TIMER_Period           = BRD_CPU_CLK / (presc * freq) - 1;   // ������ �������, (��� -1 ������ ��������� ������� ������� � DAC �� DMA)
}


void BRD_Timer_Init(Timer_Obj *TimerObj, TIMER_CntInitTypeDef *TimerInitStruct)
{
  // ��������� ������������ �������
  RST_CLK_PCLKcmd (TimerObj->ClockMask, ENABLE);

  // ��������������� �������
  TIMER_DeInit (TimerObj->TIMERx);

  // ����� ������������ �������� ������� ������� 
  TIMER_BRGInit (TimerObj->TIMERx, TimerObj->ClockBRG);

 // ������������� �������
  TIMER_CntInit (TimerObj->TIMERx, TimerInitStruct);
}

void BRD_Timer_Start(Timer_Obj *TimerObj)
{
  TIMER_Cmd (TimerObj->TIMERx, ENABLE);
}

void BRD_Timer_InitIRQ(Timer_Obj *TimerObj, uint32_t priority)
{
  // ����� ���������� ����������
  TIMER_ITConfig (TimerObj->TIMERx, TimerObj->EventIT, ENABLE);
  
  // ���������� ���������� ���������� ���������� �� �������
  NVIC_SetPriority (TimerObj->IRQn, 1);

  // ��������� ���������� ���������� �� ������� 
  NVIC_EnableIRQ (TimerObj->IRQn);
}

//// ���������� ���������� ���������� �� ������� TIMER1
//void Timer1_IRQHandler (void)
//{
//  // ����� ���������� �� ������� TIMER1
//  TIMER_ClearITPendingBit (MDR_TIMER1, TIMER_STATUS_CNT_ARR);
//}
