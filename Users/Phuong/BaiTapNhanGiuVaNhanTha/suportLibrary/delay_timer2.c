#include "delay_timer2.h"

static __IO uint32_t TimingDelayTimer2;
unsigned long miliSecondTimer2;

void delay_ms_timer2(__IO uint32_t nTime)
{ 
  TimingDelayTimer2 = nTime;
  while(TimingDelayTimer2 != 0);
}

void Timer2_Decrement(void)
{
  if (TimingDelayTimer2 != 0x00)
  { 
    TimingDelayTimer2--;
  }
}

void configDelayTimer2(void)
{
	setUpTimer(TIM2,420,200);
	configNVICTimer(TIM2_IRQn);
	startTimer(TIM2);
}

void TIM2_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET){
		//Doing somethings
		Timer2_Decrement();
		miliSecondTimer2++;
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	}
}

unsigned long getMiliSecond(void)
{
	return miliSecondTimer2;
}