//hahahah co thay phuong khong
//Nguyen tri phuong
#include "utilityGPIO.h"

void blinkGpio(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIO_ToggleBits(GPIOx,GPIO_Pin);
	delay_ms(200);
}

void xuLyNutNhan(uint16_t * numberPressButton, uint16_t *tempPress, unsigned long *miliSecond)
{
	
	int pastTime = 0;
	
	if(*numberPressButton != 0){
		pastTime = *miliSecond;
		*tempPress = *numberPressButton;
		while(*miliSecond - pastTime < 1000){
			if(*tempPress != *numberPressButton){
				pastTime = *miliSecond;
				*tempPress = *numberPressButton;
			}
		}
		*numberPressButton = 0;
	}
}

uint8_t GPIO_ReadBit(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	return GPIO_ReadInputDataBit(GPIOx, GPIO_Pin);
}
