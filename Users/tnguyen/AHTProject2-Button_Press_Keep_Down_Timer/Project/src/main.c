// Nhan nut KEY1 1-2 lan: chop led2
// Nhan nut KEY1 >=3 lan: chop led3
// Nhan giu KEY1 3s<timer<4s chop led2 & led3
// Nhan giu KEY1 >5s led2 & led3 chop luan phien

#include "stm32f4xx.h"
#include "delay.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

int  PushButton=0, temp=0;
int a=0, b=0,c=0, n=0,m=0;

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
void Key1_PE3_Interrupt(void)
	{
	
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    /* Enable clock for GPIOE */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    /* Enable clock for SYSCFG */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    /* Tell system that you will use PE4 for EXTI_Line4 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
    
    /* PE4 is connected to EXTI_Line4 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line3;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);
 
    /* Add IRQ vector to NVIC */
    /* PE4 is connected to EXTI_Line4, which has EXTI4_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}

    /* Set interrupt handlers */
    /* Handle KEY1 interrupt */
void EXTI3_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) 
		{
      
			if (PushButton==0)
			{
			  n=0; 
				TIM_Cmd(TIM2, ENABLE);
				TIM_Cmd(TIM3, ENABLE);
				TIM_Cmd(TIM4, ENABLE);
			}
			PushButton++;
			
			/* Clear interrupt flag */
		    EXTI_ClearITPendingBit(EXTI_Line3);
    }
}
 

void Timer2_Init()
{
    // Enable clock for TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    // TIM2 initialization overflow every 500ms
    // TIM2 by default has clock of 84MHz
    // Here, we must set value of prescaler and period,
    // so update event is 0.5Hz or 500ms
    // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * 
    // (TIM_Period + 1))
    // Update Event (Hz) = 84MHz / ((4199 + 1) * (9999 + 1)) = 2 Hz
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 4199;
    TIM_TimeBaseInitStruct.TIM_Period = 59999;  // 1/3Hz # 3 seconds
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // TIM2 initialize
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    // Start TIM2
    TIM_Cmd(TIM2, DISABLE);
    //TIM_Cmd(TIM2, ENABLE);
    // Nested vectored interrupt settings
    // TIM2 interrupt is most important (PreemptionPriority and 
    // SubPriority = 0)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void Timer3_Init()
{
    // Enable clock for TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // TIM2 initialization overflow every 500ms
    // TIM2 by default has clock of 84MHz
    // Here, we must set value of prescaler and period,
    // so update event is 0.5Hz or 500ms
    // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * 
    // (TIM_Period + 1))
    // Update Event (Hz) = 84MHz / ((4199 + 1) * (9999 + 1)) = 2 Hz
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8399;
    TIM_TimeBaseInitStruct.TIM_Period = 39999;  // 1/4Hz # 4 seconds
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // TIM2 initialize
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    // Start TIM2
    TIM_Cmd(TIM3, DISABLE);
    //TIM_Cmd(TIM3, ENABLE);
    // Nested vectored interrupt settings
    // TIM2 interrupt is most important (PreemptionPriority and 
    // SubPriority = 0)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void Timer4_Init()
{
    // Enable clock for TIM4
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    // TIM2 initialization overflow every 500ms
    // TIM2 by default has clock of 84MHz
    // Here, we must set value of prescaler and period,
    // so update event is 0.5Hz or 500ms
    // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * 
    // (TIM_Period + 1))
    // Update Event (Hz) = 84MHz / ((4199 + 1) * (9999 + 1)) = 2 Hz
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8399;
    TIM_TimeBaseInitStruct.TIM_Period = 49999;  // 1/5Hz # 5 seconds
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // TIM4 initialize
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    // Start TIM4
    TIM_Cmd(TIM4, DISABLE);
    //TIM_Cmd(TIM4, ENABLE);
    // Nested vectored interrupt settings
    // TIM2 interrupt is most important (PreemptionPriority and 
    // SubPriority = 0)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
    //After that, we must write code for interrupt handler that will be call every timer interrupt (500ms)
    //In this handler, we write code for toggle LED.
void TIM2_IRQHandler()
{
    // Checks whether the TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
     
			if (((PushButton==2)||(PushButton==4))&& (m==0)) 
			{
			 m=1;
			 n=1;
			}
			else if (PushButton>=5)
			{
				m=2;
				n=1;
			}
		  TIM_Cmd(TIM2, DISABLE);
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
void TIM3_IRQHandler()
{
    // Checks whether the TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
     if ((PushButton==2)&& (m==0)) 
			{
			 m=3;
			 n=1;
			 TIM_Cmd(TIM3, DISABLE);
			}
			
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
void TIM4_IRQHandler()
{
    // Checks whether the TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM4, TIM_IT_Update))
    {
     if ((PushButton==1)&& (m==0)) 
			{
			 m=4;
			 n=1;
			 TIM_Cmd(TIM4, DISABLE);
			}
			
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
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

int main(void) 
{
Clock_Init(); 
  if (SysTick_Config(SystemCoreClock / 1000))  /* SysTick 1 msec interrupts  */
  {  
		while (1);                                /* Capture error              */
  }
Key1_PE3_Interrupt();
Led_Init();
Timer2_Init();
TIM2_IRQHandler();
Timer3_Init();
TIM3_IRQHandler();
Timer4_Init();
TIM4_IRQHandler();
  while (1) 
  {
		 if (n==1)
			{
		
		switch(m)

		{ case 0:
		    break;
		  case 1: {GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
			      delay_ms(500);}
		    break;
		  case 2:{GPIO_ToggleBits(GPIOA, GPIO_Pin_1);
			      delay_ms(500);}
		    break;
		  case 3:{GPIO_ToggleBits(GPIOA, GPIO_Pin_1);
			        GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
			        delay_ms(500);}
		    break;
		  case 4:{GPIO_SetBits(GPIOA, GPIO_Pin_1);
			        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
				      delay_ms(500);
			        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			        GPIO_SetBits(GPIOA, GPIO_Pin_5);
			        delay_ms(500);}
		    break;
//		 default: {GPIO_SetBits(GPIOA, GPIO_Pin_1);
//			      GPIO_SetBits(GPIOA, GPIO_Pin_5);}
		}	 

 		}	
  }
}

