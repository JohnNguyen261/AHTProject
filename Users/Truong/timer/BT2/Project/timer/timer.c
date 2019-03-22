#include "timer.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "clock.h"
#include "delay.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
char str1[15]="RCC_APB1Periph_";
char str2[5]="_IRQn";
char tim2[4]="TIM2";
char tim3[4]="TIM3";
char tim4[4]="TIM4";
char tim5[4]="TIM5";
u16 Period, Prescaler;
void setup_timer(u16 *TIMx, uint16_t time)
{
	Period=21000;
	Prescaler=(84000*time)/21000;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(if(),ENABLE); 
	
	TIM_TimeBaseInitStructure.TIM_Period = 21000; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler= Prescaler;  
	
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIMx,DISABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void start_timer(u16 timer)
{
	TIM_Cmd(TIMx,ENABLE); 
}

void stop_timer(u16 timer)
{
	TIM_Cmd(TIMx,DISABLE); 
}