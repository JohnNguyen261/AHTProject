#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "delay.h"
unsigned int tt=0,tim,timA=0,timB=0;
void SysTick_Handler()
{
	TimingDelay_Decrement();
}

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* set PD12, PD13, PD14 and PD15 in menjadi output mode push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	/* Set pin as input */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void timer2_config()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 999;
    TIM_TimeBaseInitStruct.TIM_Period = 83;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, DISABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

void Interrupt_ConfigE3(void) 
	{
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
    EXTI_InitStruct.EXTI_Line = EXTI_Line3;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStruct);
 
    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
	

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
				tim ++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void EXTI3_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
			TIM_Cmd(TIM2, ENABLE);
			if(tt==1) {
				timA = tim;
			}
			else if (tt==2)	{
				timB = tim - timA;
				tt=0;
				tim=0;
				TIM_Cmd(TIM2, DISABLE);
			}
			tt++;
      EXTI_ClearITPendingBit(EXTI_Line3);
    }
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
int main(void)
{
	init_Clock();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/*--------------------------Initialize Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	GPIO_Config();
	timer2_config();
	Interrupt_ConfigE3();
	while(1){
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		delay_ms(timA);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		delay_ms(timB);
	}
}