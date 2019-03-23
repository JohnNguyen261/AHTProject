#ifndef UTILITY_GPIO_H
#define UTILITY_GPIO_H
	
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"

void xuLyNutNhan(uint16_t * numberPressButton, uint16_t *tempPress, unsigned long *miliSecond);
void blinkGpio(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
uint8_t GPIO_ReadBit(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);

#endif
