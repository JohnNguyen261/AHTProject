#ifndef CONFIG_GPIO_H
#define CONFIG_GPIO_H
	
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"

void configGPIO(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode);
void configEXTI_GPIO(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex, uint32_t EXTI_Linex);
void configNVIC_GPIO(uint8_t EXTIx_IRQn, uint8_t Preemption, uint8_t Sub);
void configGpioE4HaveIRQ(void);
void configGpioE3HaveIRQ(void);

#endif
