#ifndef _TIMER_H
#define _TIMER_H
	
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"

void configTimer5(uint16_t TIM_Prescaler, uint32_t TIM_Period);
void setUpTimer(TIM_TypeDef* TIMx,uint16_t TIM_Prescaler, uint32_t TIM_Period);
void configNVICTimer(uint8_t TIMx_IRQn);

void startTimer(TIM_TypeDef* TIMx);
void stopTimer(TIM_TypeDef* TIMx);


#endif
