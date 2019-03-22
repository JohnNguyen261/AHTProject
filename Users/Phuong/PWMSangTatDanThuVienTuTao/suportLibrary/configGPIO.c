#include "configGPIO.h"

void configGPIO(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	if(GPIOx == GPIOA)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	}
	else if(GPIOx == GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	}
	else if(GPIOx == GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	}
	else if(GPIOx == GPIOD)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	}
	else if(GPIOx == GPIOE)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	}
	else if(GPIOx == GPIOF)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	}
	else if(GPIOx == GPIOG)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	}
	else if(GPIOx == GPIOH)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	}
	else if(GPIOx == GPIOI)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	}
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void configEXTI_GPIO(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex, uint32_t EXTI_Linex)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOx, EXTI_PinSourcex);
	EXTI_InitStruct.EXTI_Line = EXTI_Linex;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
}

void configNVIC_GPIO(uint8_t EXTIx_IRQn, uint8_t Preemption, uint8_t Sub)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	NVIC_InitStruct.NVIC_IRQChannel = EXTIx_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = Preemption;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = Sub;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
}

void configGpioE3HaveIRQ(void)
{
	configGPIO(GPIOE, GPIO_Pin_3, GPIO_Mode_IN);
	configEXTI_GPIO(EXTI_PortSourceGPIOE, EXTI_PinSource3, EXTI_Line3);
	configNVIC_GPIO(EXTI3_IRQn, 0x00, 0x00);
}

void configGpioE4HaveIRQ(void)
{
	configGPIO(GPIOE, GPIO_Pin_4, GPIO_Mode_IN);
	configEXTI_GPIO(EXTI_PortSourceGPIOE, EXTI_PinSource4, EXTI_Line4);
	configNVIC_GPIO(EXTI4_IRQn, 0x00, 0x00);
}
