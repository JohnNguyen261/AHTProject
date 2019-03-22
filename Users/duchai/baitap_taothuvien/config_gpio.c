#include "config_gpio"
//cau hinh output
void GPIO_OUTPUT(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}
//cau hinh input
void GPIO_INPUT(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
} 
// cau hinh ngat
void EXTI_GPIO(uint32_t EXTI_Linex, uint8_t EXTI_PinSourcex)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSourcex);	
	/* PD0 is connected to EXTI_Line0 */
	EXTI_InitStruct.EXTI_Line = EXTI_Linex;
	/* Enable interrupt */
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	/* Interrupt mode */
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* Triggers on rising and falling edge */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	/* Add to EXTI */
	EXTI_Init(&EXTI_InitStruct);
}
// uu tien
void NVIC_GPIO(uint8_t EXTIx_IRQn)
{
	NVIC_InitTypeDef NVIC_InitStruct;
  

	NVIC_InitStruct.NVIC_IRQChannel = EXTIx_IRQn;
	/* Set priority */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	/* Set sub priority */
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	/* Enable interrupt */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	/* Add to NVIC */
	NVIC_Init(&NVIC_InitStruct);
	
}
void configGpioE2HaveIRQ(void)
{
	configGPIOInput(GPIOE,GPIO_Pin_2);
	configEXTIGpio(EXTI_Line3,EXTI_PinSource2);
	configNVICGpio(EXTI2_IRQn);
}

void configGpioE3HaveIRQ(void)
{
	configGPIOInput(GPIOE,GPIO_Pin_2);
	configEXTIGpio(EXTI_Line4,EXTI_PinSource2);
	configNVICGpio(EXTI2_IRQn);
}
