#ifndef __PWM_H_
#define __PWM_H_

#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"


/* SET UP PWM WITH TIMER 5 
	 periodPWM : Hz 
*/
void SETUP_PWM_TIMER5(uint32_t periodPWM);

#endif