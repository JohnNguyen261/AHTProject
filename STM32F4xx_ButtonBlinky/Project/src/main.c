#include "delay.h"
//#include "stm32f4xx.h"
//#include "stm32f4xx_conf.h"
//#include "stm32f4xx_gpio.h"

/*Definisi pin I/O*/
#define PORTLed				GPIOA
#define PORTButton		GPIOE
#define Led2					GPIO_Pin_6	
#define Led1					GPIO_Pin_7	
#define UserButton		GPIO_Pin_4	
#define UserButton1		GPIO_Pin_3	

#define RESET 				0

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
	/* enable GPIOD (PORT yang terpasang led)*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
	/* set PD12, PD13, PD14 and PD15 in menjadi output mode push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*setting PORT User Button*/
	/* enable GPIOD (PORT yang terpasang led)*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

int main(){
	
	/*--------------------------Inisialisasi Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	/*---------------Inisialisasi Periperal yang akan digunakan-----------------*/
	init_GPIO();																	/* inisialisasi GPIO					*/
	while(1){
		uint8_t currentButtonStatus = GPIO_ReadInputDataBit(PORTButton, UserButton);
		uint8_t currentButton1Status = GPIO_ReadInputDataBit(PORTButton, UserButton1);
		//GPIO_SetBits(PORTLed,Led2);
		//delay_ms(1000);
		//GPIO_ResetBits(PORTLed,Led2);
		//GPIO_SetBits(PORTLed,Led1);
		//delay_ms(1000);
		//GPIO_ResetBits(PORTLed,Led1);
		if (currentButtonStatus == 0x00)
		{
			GPIO_ResetBits(PORTLed,Led2);
		}
		else if (currentButton1Status == 0x00)
		{
			GPIO_ResetBits(PORTLed,Led1);
		}
		GPIO_SetBits(PORTLed,Led2);
		GPIO_SetBits(PORTLed,Led1);
	}
}
