#ifndef CONFIG_GPIO_H
#define CONFIG_GPIO_H
	
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"

void configGPIOInput(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
void configGPIOOutput(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
void configEXTIGpio(uint32_t EXTI_Linex, uint8_t EXTI_PinSourcex );
void configNVICGpio(uint8_t EXTIx_IRQn);
void configGpioE4HaveIRQ(void);
void configGpioE3HaveIRQ(void);

#endif
