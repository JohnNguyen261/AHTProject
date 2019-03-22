#include "delay.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"

//Interrupt Systick
void SysTick_Handler()
{
	TimingDelay_Decrement();
}

void init_GPIO()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//Led
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Button
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}


int main(){
	
	//Initialized Clock
	SystemCoreClockUpdate();                     
  if (SysTick_Config(SystemCoreClock / 1000)){ 
    while (1);                                  
  }
	
	//Initialized GPIO
	init_GPIO();															
	while (1)
	{
    if (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0){
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
    }
    else{
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);
    }
	}
}
