
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

void TIM2_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET){
		//Doing somethings
		Timer2_Decrement();
		miliSecondTimer2++;
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	}
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
	configGPIOOutput(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
	configGpioE3HaveIRQ();
	configGpioE4HaveIRQ();
	configTimer5(420,200);
	configDelayTimer2();
	
	
	while(1)
	{
		
		xuLyNutNhan(&numberPress,&chuongTrinhLed,&miliSecondTimer2);
		
		switch(chuongTrinhLed)
		{
			case 1:
				GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
				delay_ms_timer2(200);
				break;
			
			case 2:
				GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
				delay_ms_timer2(200);
				break;
			
			case 3:
				GPIO_ToggleBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
				delay_ms_timer2(200);
				break;
			
			case 4:
				GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
				delay_ms_timer2(200);
				GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
				delay_ms_timer2(200);
				break;
			
			default:
				break;
		}
		
	}
}
