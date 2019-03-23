#ifndef CONFIG_PWM_H
#define CONFIG_PWM_H
	
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"
#include "Timer.h"
#include "configGPIO.h"

void configPWMChannel1(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSourcex);
void configPWMChannel2(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSourcex);
void configPWMChannel3(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSourcex);
void configPWMChannel4(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSourcex);
void setUpPWMChannel1(TIM_TypeDef* TIMx, uint32_t TIM_Pulse);
void setUpPWMChannel2(TIM_TypeDef* TIMx, uint32_t TIM_Pulse);
void setUpPWMChannel3(TIM_TypeDef* TIMx, uint32_t TIM_Pulse);
void setUpPWMChannel4(TIM_TypeDef* TIMx, uint32_t TIM_Pulse);
void configPWM_A6(void);
void configPWM_A7(void);
void SetCompare_A6(uint32_t Compare1);
void SetCompare_A7(uint32_t Compare2);

#endif
