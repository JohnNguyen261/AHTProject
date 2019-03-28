#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "uart_to_printf.h"
#include "delay.h"
/*---------------------------Interrupt Systick-------------------------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}
//void gpio_config(){
//	GPIO_InitTypeDef GPIO_InitStruct;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//	/* set PD12, PD13, PD14 and PD15 in menjadi output mode push pull */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOA, &GPIO_InitStruct);
//}

int count=0;
void init_Clock()
{
// Resets the clock configuration to the default reset state
RCC_DeInit();

// Enable external crystal (HSE)
RCC_HSEConfig(RCC_HSE_ON);
// Wait until HSE ready to use or not
ErrorStatus errorStatus = RCC_WaitForHSEStartUp();

if (errorStatus == SUCCESS)
{
// Configure the PLL for 168MHz SysClk and 48MHz for USB OTG, SDIO
RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);
// Enable PLL
RCC_PLLCmd(ENABLE);
// Wait until main PLL clock ready
while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

// Set flash latency
FLASH_SetLatency(FLASH_Latency_5);

// AHB 168MHz
RCC_HCLKConfig(RCC_SYSCLK_Div1);
// APB1 42MHz
RCC_PCLK1Config(RCC_HCLK_Div4);
// APB2 84 MHz
RCC_PCLK2Config(RCC_HCLK_Div2);

// Set SysClk using PLL
RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}
else
{
// Do something to indicate that error clock configuration
while (1);
}

SystemCoreClockUpdate();
}
int main(void)
{
	init_Clock();
		/*--------------------------Initialize Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	UART_Configuration();
	printf("Hi! I'm Hung\n");
	while (1)
    {
			printf("count = %d\n",count++);
			delay_ms(1000);
		}
}