#include "PWM_H.h"

void SETUP_PWM_TIMER5(uint32_t periodPWM) {
	
		uint32_t period = (84000000/periodPWM)-1;
	
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   
    TIM_BaseStruct.TIM_Prescaler = 0;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_BaseStruct.TIM_Period = period; /* kHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    
    TIM_TimeBaseInit(TIM5, &TIM_BaseStruct);
    
    TIM_Cmd(TIM5, ENABLE);

    TIM_OCInitTypeDef TIM_OCStruct;
	
    /* Common settings */   
    /* PWM mode 2 = Clear on compare match */
    /* PWM mode 1 = Set on compare match */
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
     
    //TIM_OCStruct.TIM_Pulse = 0; /* 50% duty cycle */
    TIM_OC2Init(TIM5, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
 
}