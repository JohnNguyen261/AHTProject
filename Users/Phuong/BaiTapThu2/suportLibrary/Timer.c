#include "Timer.h"

void configTimer5(uint16_t TIM_Prescaler, uint32_t TIM_Period)
{
	setUpTimer(TIM5,RCC_APB1Periph_TIM5,TIM_Prescaler,TIM_Period);
	configNVICTimer(TIM5_IRQn);
}

void setUpTimer(TIM_TypeDef* TIMx, uint32_t RCC_APB1Periph_TIMx,uint16_t TIM_Prescaler, uint32_t TIM_Period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx,ENABLE);
	TIM_TimeBaseInitStruct.TIM_Prescaler = TIM_Prescaler;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = TIM_Period; //((84000000*time)/(420*1000));
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);
	
}

void configNVICTimer(uint8_t TIMx_IRQn)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIMx_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void startTimer(TIM_TypeDef* TIMx)
{
	TIM_Cmd(TIMx, ENABLE);
}

void stopTimer(TIM_TypeDef* TIMx)
{
	TIM_Cmd(TIMx, DISABLE);
}

