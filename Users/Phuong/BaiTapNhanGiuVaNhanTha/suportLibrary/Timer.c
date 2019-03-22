#include "Timer.h"

void configTimer5(uint16_t TIM_Prescaler, uint32_t TIM_Period)
{
	setUpTimer(TIM5,TIM_Prescaler,TIM_Period);
	configNVICTimer(TIM5_IRQn);
}

void setUpTimer(TIM_TypeDef* TIMx,uint16_t TIM_Prescaler, uint32_t TIM_Period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	if(TIMx == TIM1){
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	}
	else if(TIMx == TIM2){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	}
	else if(TIMx == TIM3){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	}
	else if(TIMx == TIM4){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	}
	else if(TIMx == TIM5){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	}
	else if(TIMx == TIM6){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	}
	else if(TIMx == TIM7){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	}
	else if(TIMx == TIM8){
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	}
	else if(TIMx == TIM9){
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
	}
	else if(TIMx == TIM10){
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
	}
	else if(TIMx == TIM11){
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
	}
	else if(TIMx == TIM12){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	}
	else if(TIMx == TIM13){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);
	}
	else if(TIMx == TIM14){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
	}
	
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

