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
#define UserButton		GPIO_Pin_3	

// bai tap 2


// viet them 
int tt=0;

/*deklarasi struct*/
GPIO_InitTypeDef GPIO_InitStructure;

/*deklarasi fungsi*/
void init_GPIO(void);


/*---------------------------Interrupt Systick-------------------------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}


void init_GPIO()
{
	/*setting PORT Led*/
	/* enable GPIOD (PORT led)*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* set PD12, PD13, PD14 and PD15 in menjadi output mode push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*setting PORT User Button*/
	/* enable GPIOD (PORT led)*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}


int main(){
	
	/*--------------------------Initialize Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	/*---------------Initialize Peripheral-----------------*/
	init_GPIO();																	/* Initialize GPIO					*/
	while(1)
		{
		if(!(GPIO_ReadInputData(PORTButton)&GPIO_Pin_4))
			{
				GPIO_ResetBits(PORTLed,GPIO_Pin_7);
			}
			else GPIO_SetBits(PORTLed,GPIO_Pin_7);
}
}		
				
