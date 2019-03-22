#include "delay.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

//Interrupt Systick
void SysTick_Handler()
{
	TimingDelay_Decrement();
}

void Interrupt_PE2(void) {
    //Variable
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    //Clock GPIOE
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    //Clock SYSCFG 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    //Button input
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    //Use PE2
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStruct);
 
		//Nested vectored interrupt
    NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_Init(&NVIC_InitStruct);
}
//
void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2))
    {
        GPIO_ToggleBits(GPIOA, GPIO_Pin_1);
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}



void init_GPIO()
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
    //Initialized Clock
	SystemCoreClockUpdate();                      
  if (SysTick_Config(SystemCoreClock / 1000)) { 
    while (1);                                  
  }
	//Initialized GPIO
	init_GPIO();
	Interrupt_PE2();
	
	while(1){
		 GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		 delay_ms(500);
	}
}









































///*deklarasi struct*/
//GPIO_InitTypeDef GPIO_InitStructure;

///*deklarasi fungsi*/
//void init_GPIO(void);


///*---------------------------Interrupt Systick-------------------------------*/
//void SysTick_Handler()
//{
//	TimingDelay_Decrement();
//}


//void init_GPIO()
//{
//	/*setting PORT Led*/
//	/* enable GPIOD (PORT led)*/
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//	/* set PD12, PD13, PD14 and PD15 in menjadi output mode push pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	/*setting PORT User Button*/
//	/* enable GPIOD (PORT led)*/
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOE, &GPIO_InitStructure);
//}


//int main(){
//	
//	/*--------------------------Initialize Clock------------------------------*/
//	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
//  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
//    while (1);                                  /* Capture error              */
//  }
//	
//	/*---------------Initialize Peripheral-----------------*/
//	init_GPIO();																	/* Initialize GPIO					*/
//	while(1){
//		GPIO_SetBits(PORTLed,GPIO_Pin_1);
//		delay_ms(500);
//		GPIO_ResetBits(PORTLed,GPIO_Pin_1);
//		GPIO_SetBits(PORTLed,GPIO_Pin_5);
//		delay_ms(500);
//		GPIO_ResetBits(PORTLed,GPIO_Pin_5);
//	}
//}
