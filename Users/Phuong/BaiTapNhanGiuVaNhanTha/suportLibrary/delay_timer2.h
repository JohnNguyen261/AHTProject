#ifndef DELAY_TIMER_2_H
#define DELAY_TIMER_2_H
	
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"
#include "Timer.h"

void delay_ms_timer2(__IO uint32_t nTime);
void Timer2_Decrement(void);
void TIM2_IRQHandler(void);
void configDelayTimer2(void);
unsigned long getMiliSecond(void);


#endif
