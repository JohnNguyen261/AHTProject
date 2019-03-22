#include "stm32f4xx.h"
#include "delay.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "timer.h"


int a=0;

void Led_Init(void)
{
			/*setting PORT Led*/
		/* enable GPIOD (PORT led)*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		/* set PD12, PD13, PD14 and PD15 in menjadi output mode push pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void Clock_Init()
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
void SysTick_Handler()
    {
	   TimingDelay_Decrement();
    }
void TIM2_IRQHandler()
{
    // Checks whether the TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
    a=1;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
int main(void) 
{
Clock_Init(); 
  if (SysTick_Config(SystemCoreClock / 1000))  /* SysTick 1 msec interrupts  */
  {  
		while (1);                                /* Capture error              */
  }
//Key1_PE3_Interrupt();
Led_Init();
Set_Timer(TIM2, 4199, 9999 );
TIM2_IRQHandler();
 while (1) 
  { if (a==1){
	  GPIO_ToggleBits(GPIOA, GPIO_Pin_1);
		delay_ms(500);
	}
  }
}

