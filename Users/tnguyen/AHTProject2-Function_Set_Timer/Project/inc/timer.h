#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f4xx_tim.h"

#define delay_const  (unsigned long) (336000000 / 15574784)

// /* Private function prototypes -----------------------------------------------*/
void Set_Timer(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t Period );
// void delay_ms(__IO uint32_t nTime);
// void delay_us(__IO uint32_t xx);
// void TimingDelay_Decrement(void);

#endif
