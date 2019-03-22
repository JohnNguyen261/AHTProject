#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"


void SETUP_TIMER2(uint32_t TIM_MS, uint8_t PrePriority );

#endif