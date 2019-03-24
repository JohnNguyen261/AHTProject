#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "delay.h"

u32 i=0;

void SysTick_Handler()
{
	TimingDelay_Decrement();
}

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
void TM_LEDS_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
 
void TM_TIMER_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_BaseStruct.TIM_Prescaler = 0;

    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_BaseStruct.TIM_Period = 83; /* 1MHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_BaseStruct);

}
 
void TM_PWM_Init(void) {
    TIM_OCInitTypeDef TIM_OCStruct;
    /* Common settings */
    
    /* PWM mode 2 = Clear on compare match */
    /* PWM mode 1 = Set on compare match */
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    
/*
    To get proper duty cycle, you have simple equation
    
    pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1
    
    where DutyCycle is in percent, between 0 and 100%
    
    25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
    50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
    75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
    100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399
    
    Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
*/
    TIM_OCStruct.TIM_Pulse = 0; 
    TIM_OC1Init(TIM3, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    
    TIM_OCStruct.TIM_Pulse = 0; 
    TIM_OC2Init(TIM3, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
		TIM_ARRPreloadConfig(TIM3, ENABLE);
		TIM_Cmd(TIM3, ENABLE);
		
}

int main(void) {
		init_Clock();
		/*--------------------------Initialize Clock------------------------------*/
		SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
		if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
			while (1);                                  /* Capture error              */
		}
    TM_LEDS_Init();
    TM_TIMER_Init();
    TM_PWM_Init();
    while (1) 
			{
				for(i=0;i<83;i++)
				{
					//TIM_SetCompare1(TIM3,i);
					//TIM_SetCompare2(TIM3,i);
				  TIM3->CCR1 = i;
					TIM3->CCR2 = i ;
					delay_ms(10);
				}
				for(i=83;i>0;i--)
				{
					//TIM_SetCompare1(TIM3,i);
					//TIM_SetCompare2(TIM3,i);
					TIM3->CCR1 = i;
					TIM3->CCR2 = i ;
					delay_ms(10);
				}
			}
}
