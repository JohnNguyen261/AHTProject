#ifndef MANAGE_IRQ_H
#define MANAGE_IRQ_H
	
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"

void TIM2_IRQHandler(void);
void EXTI4_IRQHandler(void); 
#endif
