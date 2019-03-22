#ifndef CONFIG_GPIO_H
#define CONFIG_GPIO_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"

void GPIO_INPUT(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
void GPIO_OUTPUT(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
void EXTI_GPIO(uint32_t EXTI_Linex, uint8_t EXTI_PinSourcex );
void NVIC_GPIO(uint8_t EXTIx_IRQn);
void configGpioE2HaveIRQ(void);
void configGpioE3HaveIRQ(void);

#endif