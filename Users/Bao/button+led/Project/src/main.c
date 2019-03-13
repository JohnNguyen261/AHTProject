#include "delay.h"
//#include "stm32f4xx.h"
//#include "stm32f4xx_conf.h"
//#include "stm32f4xx_gpio.h"
void SysTick_Handler()
{
	TimingDelay_Decrement();
}
int main(){
	
	SystemCoreClockUpdate();                      
  if (SysTick_Config(SystemCoreClock / 1000)) { 
    while (1);                                  
  }
	RCC->AHB1ENR=0x00000011;
	GPIOA->MODER=0x00005000;
	GPIOE->MODER&=0xfffffc3f;
	GPIOE->PUPDR=0x55555555;
	while(1){
		GPIOA->ODR|=0x00000080;
		GPIOA->ODR|=0x00000040;
		if(!(GPIOE->IDR& 0x00000008))
		{
	  	GPIOA->ODR&=0xffffff7f;
		}
		if(!(GPIOE->IDR& 0x00000010))
		{
		  GPIOA->ODR&=0xffffffbf;
		}
	}
}
