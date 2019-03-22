
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "configGPIO.h"
#include "utilityGPIO.h"
#include "Timer.h"
#include "configPLL.h"
#include "delay_timer2.h"

uint16_t numberPress = 0;
uint16_t chuongTrinhLed = 0;

unsigned long timerAfter = 0;
unsigned long timerBefore = 0;

unsigned long miliSecondTimer5 = 0;
unsigned long miliSecondTimer2 = 0;

void TM_TIMER_Init(void) 
{
	TIM_TimeBaseInitTypeDef TIM_BaseStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_BaseStruct.TIM_Period = 100; /* 10kHz PWM */
	TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_BaseStruct);
	TIM_Cmd(TIM3, ENABLE);
}
	
void TM_PWM_Init(void) 
{
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCStruct.TIM_Pulse = 99; /* 25% duty cycle */
	TIM_OC1Init(TIM3, &TIM_OCStruct);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_OCStruct.TIM_Pulse = 50; /* 50% duty cycle */
	TIM_OC2Init(TIM3, &TIM_OCStruct);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

void TM_LEDS_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Alternating functions for pins */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
	
	/* Set pins */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void EXTI3_IRQHandler(void) 
{
	if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
			//Doing somethings
			numberPress++;
			EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void TIM5_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) != RESET){
		//Doing somethings
		miliSecondTimer5++;
		TIM_ClearFlag(TIM5,TIM_FLAG_Update);
	}
}


void EXTI4_IRQHandler(void) 
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
			//Doing somethings
			miliSecondTimer5 = 0;
			if(GPIO_ReadBit(GPIOE,GPIO_Pin_4) == 0)
			{
				startTimer(TIM5);
				while(GPIO_ReadBit(GPIOE,GPIO_Pin_4) == 0)
				{
					TIM5_IRQHandler();
				}
				stopTimer(TIM5);
				if(miliSecondTimer5 >= 4000){
					chuongTrinhLed = 4;
				}
			}
			EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

int main(void)
{
	init_Clock();
	configDelayTimer2();
	
	TM_TIMER_Init();
	TM_PWM_Init();
	TM_LEDS_Init();
	
	int i = 0;
	while(1)
	{
		for(i=0;i<100;i++)
		{
			TIM_SetCompare1(TIM3,i);
			TIM_SetCompare2(TIM3,i);
			delay_ms_timer2(20);
		}
		
		for(i=100;i>0;i--)
		{
			TIM_SetCompare1(TIM3,i);
			TIM_SetCompare2(TIM3,i);
			delay_ms_timer2(20);
		}
	}
}
