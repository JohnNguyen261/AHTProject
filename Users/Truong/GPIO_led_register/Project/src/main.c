#include "delay.h"
//#include "stm32f4xx.h"
//#include "stm32f4xx_conf.h"
//#include "stm32f4xx_gpio.h"

void init_GPIO(void);

/*---------------------------Interrupt Systick-------------------------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}


void init_GPIO()
{
	RCC->AHB1ENR = 0xffffffff;
	GPIOA->MODER = 0x00005000;
	GPIOA->ODR = 0x00000000;
}

int main(){
	
	/*--------------------------Initialize Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	/*---------------Initialize Peripheral-----------------*/
	init_GPIO();																	/* Initialize GPIO					*/
	while(1){
		GPIOA->ODR^=1<<6;
		delay_ms(500);
		GPIOA->ODR^=1<<7;
	}
}
