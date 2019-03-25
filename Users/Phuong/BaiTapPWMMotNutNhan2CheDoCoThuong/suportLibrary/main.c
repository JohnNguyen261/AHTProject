
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

int Level,LevelPWM;

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

void TroChoiPowerLed(int Level, int LevelPWM)
{
	if(Level >= (LevelPWM - 10) && Level <= (LevelPWM + 10))
	{
		for(int i=0;i<10;i++)
		{
			GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
			delay_ms_timer2(200);
		}
	}
	else
	{
		for(int i=0;i<5;i++)
		{
			GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
			delay_ms_timer2(1000);
		}
	}
}

void ProgramLedPWM(uint16_t * statusButton)
{
	if(*statusButton == 1)
	{
		delay_ms_timer2(200);
		if(*statusButton == 1)
		{
			LevelPWM = 0;
			int StatusAmDuong = 1;
			while(*statusButton == 1)
			{
				SetCompare_A6(LevelPWM);
				delay_ms_timer2(10);
				if(LevelPWM > 100)
				{
					StatusAmDuong = -1;
				}
				if(LevelPWM < 0)
				{
					StatusAmDuong = 1;
				}
				LevelPWM = StatusAmDuong + LevelPWM;
			}
			TroChoiPowerLed(numberPress*25,LevelPWM);
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
	configTimer5(420,200);
	startTimer(TIM5);
	configGPIO(GPIOA,GPIO_Pin_7,GPIO_Mode_OUT);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	configPWM_A6();

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
