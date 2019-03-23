
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "configGPIO.h"
#include "utilityGPIO.h"
#include "Timer.h"
#include "configPLL.h"
#include "delay_timer2.h"
#include "configPWM.h"

unsigned long miliSecond;
unsigned long khoanThoiGian;
unsigned long pastTime;
int soLanNhan = 0;
uint16_t tempNumberPress = 0;
uint16_t numberPress = 0;
int programLed = 0;
int i = 0;

uint16_t statusButton = 0;

void EXTI4_IRQHandler(void) 
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) 
	{
			//Doing somethings

			if(statusButton == 0)
			{
				statusButton = 1;
			}
			else 
			{
				statusButton = 0;
			}
			
			EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void TIM5_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) != RESET){
		//Doing somethings
		miliSecond++;
		TIM_ClearFlag(TIM5,TIM_FLAG_Update);
	}
}

void ProgramLedPWM(uint16_t * statusButton)
{
	if(*statusButton == 1)
	{
		delay_ms_timer2(200);
		if(*statusButton == 1)
		{
			while(*statusButton == 1)
			{
				for(int i=0;i<100 && *statusButton == 1;i++)
				{
					SetCompare_A6(i);
					SetCompare_A7(i);
					delay_ms_timer2(10);
				}
				for(int i=100;i>0 && *statusButton == 1;i--)
				{
					SetCompare_A6(i);
					SetCompare_A7(i);
					delay_ms_timer2(10);
				}
			}
		}
		else
		{
			numberPress++;
			if(numberPress > 4)
			{
				numberPress = 0;
			}
		}
		
		
	}
}
int main(void)
{
	init_Clock();
	configDelayTimer2();
	configGpioE4HaveIRQ();
	configGpioE3HaveIRQ();
	configTimer5(420,200);
	startTimer(TIM5);
	configPWM_A6();
	configPWM_A7();

	while(1)
	{
		ProgramLedPWM(&statusButton);
		switch(numberPress)
		{
			case 0:
				SetCompare_A6(0);
				SetCompare_A7(0);
				break;
			case 1:
				SetCompare_A6(25);
				SetCompare_A7(25);
				break;
			case 2:
				SetCompare_A6(50);
				SetCompare_A7(50);
				break;
			case 3:
				SetCompare_A6(75);
				SetCompare_A7(75);
				break;
			case 4:
				SetCompare_A6(100);
				SetCompare_A7(100);
				break;
			default:
				break;
		}
	}
}
