#include "timerH.h"

/* SETUP TIMER 2 
	TIM_MS : period time (ms)
	PrePriority : NVIC Channel Preemption Priority
*/
void SETUP_TIMER2(uint32_t TIM_MS, uint8_t PrePriority ){
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		
		float tmp=	(float)TIM_MS/1000;
		tmp =(float) 1/tmp;
		tmp = 8400/tmp;
		uint32_t period = tmp-1;
	
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 10000;
    TIM_TimeBaseInitStruct.TIM_Period = period;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // TIM2 initialize
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    // Start TIM2
    TIM_Cmd(TIM2, ENABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = PrePriority;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}