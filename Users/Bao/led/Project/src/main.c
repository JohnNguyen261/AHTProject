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
	RCC->AHB1ENR=0x00000001;
	GPIOA->MODER=0x00005000;
	while(1){
		
		GPIOA->ODR|=0x00000080;
		GPIOA->ODR&=0xffffffbf;
		delay_ms(100);
		GPIOA->ODR&=0xffffff7f;
		GPIOA->ODR|=0x00000040;
		delay_ms(100);
	}
}
