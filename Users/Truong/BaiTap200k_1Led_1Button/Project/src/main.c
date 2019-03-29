#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "delay.h"
#define KEY_PRESSED 1 //state of key being pressed
#define KEY_NO_PRESS 0 //key not pressed
#define KEY_SHORT_PRESS 2 //key pressed short
#define KEY_LONG_PRESS 3 //key pressed long
#define KEY_DURATION 200 //cycle count, minimum threshold to test for long presses

u32 nhangiu=0, nhannha=0, duty=0;
u32 i=0, time=0, solannhan=0,k=5;
u32 status=0,TT=0, press=1, hold=2, count=0,solanngat=0;

unsigned char key_read()  {
		unsigned char count=0;
 if (status != KEY_PRESSED) return KEY_NO_PRESS; //key not pressed
 //key is pressed
 while (status == KEY_PRESSED) count+=1; //increment count if key is continuously pressed
 if (count > KEY_DURATION) return KEY_LONG_PRESS;
 else return KEY_SHORT_PRESS;
}
//unsigned char key_read()  {
//// unsigned char count=0;
// if (status != KEY_PRESSED){ TT= KEY_NO_PRESS; return KEY_NO_PRESS;}//key not pressed
// //key is pressed
// while (status == KEY_PRESSED) count+=1; //increment count if key is continuously pressed
// if (count > KEY_DURATION){ TT= KEY_LONG_PRESS;return KEY_LONG_PRESS;}
// if	(count < KEY_DURATION){ TT = KEY_SHORT_PRESS; return KEY_SHORT_PRESS;}
//}

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



void init_LED(void);

void init_LED()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Configure_PE3(void) {

    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;  

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
    

    EXTI_InitStruct.EXTI_Line = EXTI_Line3;

    EXTI_InitStruct.EXTI_LineCmd = ENABLE;

    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;

    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;

    EXTI_Init(&EXTI_InitStruct);
 

    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;

    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;

    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;

    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}

void TIM3_INT_Init()
{
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
    TIM_BaseStruct.TIM_Prescaler = 84;
    /* Count up */
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_BaseStruct.TIM_Period = 1000-1 ; /* 1kHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_BaseStruct);
}
void TIM2_INT_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1; //200ms
    TIM_TimeBaseInitStruct.TIM_Period = 1999;       //200ms
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;


    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM2, DISABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}


void TM_PWM_Init(void) {
    TIM_OCInitTypeDef TIM_OCStruct;
    
    /* Common settings */
    
    /* PWM mode 2 = Clear on compare match */
    /* PWM mode 1 = Set on compare match */
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OCStruct.TIM_Pulse = 0; /* 25% duty cycle */
    TIM_OC1Init(TIM3, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

		TIM_ARRPreloadConfig(TIM3, ENABLE);
		TIM_Cmd(TIM3, ENABLE);
}

void EXTI3_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) 
		{			
//			count++;
			solanngat++;
//			if(count==1)
//			{
//				TIM_Cmd(TIM2, ENABLE);
//			}
//			if(count==2)
//			{
//				
//				count=0;
//			}
			if(status==1)
			{
				status=0;
				}
			else status =1;
//				key_read();
    }
		EXTI_ClearITPendingBit(EXTI_Line3);
}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
//			duty = duty + k;
//			if (duty == 0 || duty > 1000) {
//					k = -k ;
//				}
//			if(solanngat==1)
//				{
////					return KEY_LONG_PRESS;
//				}
//				if(solanngat>1)
//				{
//					solannhan=solanngat/2;
//					duty=solannhan*199;
//					if(solannhan>5)	
//					{
//						solanngat=0;
//						solannhan=0;
//					}
//				}
//				TIM_Cmd(TIM2, DISABLE);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}


int main(){
	init_Clock();
	/*--------------------------Initialize Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	init_LED();
	Configure_PE3();
	TIM2_INT_Init();
	TIM3_INT_Init();
	TM_PWM_Init();
	
	while(1)
	{
//		unsigned char TT = key_read();
//		if(TT == KEY_LONG_PRESS)
//		{
				for(int i=0;i<1000 && status == 1;i++)
				{
					TIM3->CCR1 = i;
					delay_ms(2);
				}
				for(int i=1000;i>0 && status == 1;i--)
				{
					TIM3->CCR1 = i;
					delay_ms(2);
				}
			
				//delay_ms(10);
//		}
//		if(TT == KEY_SHORT_PRESS)
//		{
//			solannhan=solanngat/2;
//			duty=solannhan*249;
//			if(solannhan>4)
//			{
//				solannhan=0;
//				solanngat=0;
//			}
//			TIM3->CCR1 = duty;
//		}
	}
}
