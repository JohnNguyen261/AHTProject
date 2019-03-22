#include "configPWM.h"

void configPWMChannel1(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSourcex)
{
	setUpTimer(TIMx,0,100);
	startTimer(TIMx);
	setUpPWMChannel1(TIMx,50);
	configGPIO(GPIOx, GPIO_Pin, GPIO_Mode_AF);
	
	if(TIMx == TIM1)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM1);
	}
	else if(TIMx == TIM2)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM2);
	}
	else if(TIMx == TIM3)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM3);
	}	
	else if(TIMx == TIM4)
	{	
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM4);
	}
	else if(TIMx == TIM5)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM5);
	}
	else if(TIMx == TIM8)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM8);
	}
	else if(TIMx == TIM9)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM9);
	}
	else if(TIMx == TIM10)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM10);
	}
	else if(TIMx == TIM11)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM11);
	}
	
}

void configPWMChannel2(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSourcex)
{
	setUpTimer(TIMx,0,100);
	startTimer(TIMx);
	setUpPWMChannel2(TIMx,50);
	configGPIO(GPIOx, GPIO_Pin, GPIO_Mode_AF);
	
	if(TIMx == TIM1)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM1);
	}
	else if(TIMx == TIM2)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM2);
	}
	else if(TIMx == TIM3)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM3);
	}	
	else if(TIMx == TIM4)
	{	
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM4);
	}
	else if(TIMx == TIM5)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM5);
	}
	else if(TIMx == TIM8)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM8);
	}
	else if(TIMx == TIM9)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM9);
	}
	else if(TIMx == TIM10)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM10);
	}
	else if(TIMx == TIM11)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM11);
	}
	
}

void configPWMChannel3(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSourcex)
{
	setUpTimer(TIMx,0,100);
	startTimer(TIMx);
	setUpPWMChannel3(TIMx,50);
	configGPIO(GPIOx, GPIO_Pin, GPIO_Mode_AF);
	
	if(TIMx == TIM1)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM1);
	}
	else if(TIMx == TIM2)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM2);
	}
	else if(TIMx == TIM3)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM3);
	}	
	else if(TIMx == TIM4)
	{	
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM4);
	}
	else if(TIMx == TIM5)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM5);
	}
	else if(TIMx == TIM8)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM8);
	}
	else if(TIMx == TIM9)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM9);
	}
	else if(TIMx == TIM10)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM10);
	}
	else if(TIMx == TIM11)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM11);
	}
	
}

void configPWMChannel4(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSourcex)
{
	setUpTimer(TIMx,0,100);
	startTimer(TIMx);
	setUpPWMChannel4(TIMx,50);
	configGPIO(GPIOx, GPIO_Pin, GPIO_Mode_AF);
	
	if(TIMx == TIM1)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM1);
	}
	else if(TIMx == TIM2)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM2);
	}
	else if(TIMx == TIM3)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM3);
	}	
	else if(TIMx == TIM4)
	{	
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM4);
	}
	else if(TIMx == TIM5)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM5);
	}
	else if(TIMx == TIM8)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM8);
	}
	else if(TIMx == TIM9)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM9);
	}
	else if(TIMx == TIM10)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM10);
	}
	else if(TIMx == TIM11)
	{
		GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_TIM11);
	}
	
}
	
void setUpPWMChannel1(TIM_TypeDef* TIMx, uint32_t TIM_Pulse)
{
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCStruct.TIM_Pulse = TIM_Pulse;
	TIM_OC1Init(TIMx, &TIM_OCStruct);
	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
}

void setUpPWMChannel2(TIM_TypeDef* TIMx, uint32_t TIM_Pulse)
{
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCStruct.TIM_Pulse = TIM_Pulse;
	TIM_OC2Init(TIMx, &TIM_OCStruct);
	TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
}

void setUpPWMChannel3(TIM_TypeDef* TIMx, uint32_t TIM_Pulse)
{
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCStruct.TIM_Pulse = TIM_Pulse;
	TIM_OC3Init(TIMx, &TIM_OCStruct);
	TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
}

void setUpPWMChannel4(TIM_TypeDef* TIMx, uint32_t TIM_Pulse)
{
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCStruct.TIM_Pulse = TIM_Pulse;
	TIM_OC4Init(TIMx, &TIM_OCStruct);
	TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
}
