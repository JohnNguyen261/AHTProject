
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

void EXTI3_IRQHandler(void) 
{
	if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
			//Doing somethings
			EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI4_IRQHandler(void) 
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
			//Doing somethings
			if(soLanNhan == 0)
			{
				pastTime = getMiliSecond();
				soLanNhan++;
			}
			else
			{
				khoanThoiGian = getMiliSecond() - pastTime;
				soLanNhan = 0;
				tempNumberPress++;
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

int main(void)
{
	init_Clock();
	configDelayTimer2();
	configGpioE4HaveIRQ();
	configGpioE3HaveIRQ();
	configTimer5(420,200);
	startTimer(TIM5);
	configGPIO(GPIOA, GPIO_Pin_6|GPIO_Pin_7, GPIO_Mode_OUT);

	while(1)
	{
		xuLyNutNhan(&tempNumberPress,&numberPress,&miliSecond);
		if(numberPress == 2 && khoanThoiGian <4000)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_7);
			GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
			delay_ms_timer2(500);
		}
		else if(numberPress >=3 && numberPress <= 5 && khoanThoiGian <4000)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_6);
			GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
			delay_ms_timer2(500);
		}
		
		else if(numberPress > 5 && khoanThoiGian <4000)
		{
			GPIO_ToggleBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
			delay_ms_timer2(500);
		}
		else if(khoanThoiGian >= 4000)
		{
			GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
			delay_ms_timer2(100);
			GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
			delay_ms_timer2(100);
		}
	}
}
