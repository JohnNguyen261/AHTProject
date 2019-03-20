
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "configGPIO.h"
#include "utilityGPIO.h"
#include "Timer.h"
#include "configPLL.h"
#include "delay_timer2.h"
#include "configPWM.h"

int main(void)
{
	init_Clock();
	configDelayTimer2();
	
	configPWMChannel1(TIM3,GPIOA,GPIO_Pin_6,GPIO_PinSource6);
	configPWMChannel2(TIM3,GPIOA,GPIO_Pin_7,GPIO_PinSource7);
	
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
