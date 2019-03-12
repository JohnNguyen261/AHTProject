#include "delay.h"
//#include "stm32f4xx.h"
//#include "stm32f4xx_conf.h"
//#include "stm32f4xx_gpio.h"

/*Define pin I/O*/
#define PORTLed				GPIOA
#define PORTButton		GPIOE
#define LedHijau			GPIO_Pin_6	
#define LedOrange			GPIO_Pin_7	
#define LedMerah			GPIO_Pin_14	
#define LedBiru				GPIO_Pin_15	
#define UserButton		GPIO_Pin_2	

/*deklarasi struct*/
GPIO_InitTypeDef GPIO_InitStructure;

/*deklarasi fungsi*/
void init_GPIO(void);


/*---------------------------Interrupt Systick-------------------------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}

  



int main(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/*--------------------------Initialize Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }

	GPIOA -> MODER |= 0x00001000;
	GPIOA -> ODR |= 	0x00000040;

	while(1){
		GPIOA -> ODR |= 	0x00000040;
		delay_ms(500);
		GPIOA -> ODR &= ~0x00000040;
		delay_ms(500);
	}
}
