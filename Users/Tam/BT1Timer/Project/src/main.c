#include "delay.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"

//variable global
 int count = 0;
 int timeCount = 0;
//
void SysTick_Handler()
{
	TimingDelay_Decrement();
}
/////////////////////////////////////////

void init_Clock()
{
	// Resets the clock configuration to the default reset state
	RCC_DeInit();

	// Enable external crystal (HSE)
	RCC_HSEConfig(RCC_HSE_ON);
	// Wait until HSE ready to use or not
	


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


	SystemCoreClockUpdate();
}
////////////////////////////////////////
void TIM_INT_Init()
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	  NVIC_InitTypeDef NVIC_InitStruct;
    // Enable clock TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitStruct.TIM_Prescaler = 420;
    TIM_TimeBaseInitStruct.TIM_Period = 200;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, DISABLE);

    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

void TIM2_IRQHandler()
{
    // Checks whether the TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
				TIM_Cmd(TIM2, DISABLE);
				timeCount = count;
				count = 0;
        // Clears the TIM2 interrupt 
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
//////////////////////////////////////////////
void Interrupt_PE2(void) {
    //Variable
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    //Clock GPIOE
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    //Clock SYSCFG 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    //Button input
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    //Use PE2
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStruct);
 
		//Nested vectored interrupt
    NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_Init(&NVIC_InitStruct);
}
void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2))
    {
				TIM_Cmd(TIM2, ENABLE);
				++count; 
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}
/////////////////////////////////////////////////////
void init_GPIO()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}


int main(){
	init_Clock();
	//Initialized Clock
                      
  if (SysTick_Config(SystemCoreClock / 1000)) {
    while (1);                                  
  }
	//Initialized 
	init_GPIO();	
	TIM_INT_Init();
	Interrupt_PE2();
	while(1){
		switch(timeCount){
			case 1:
			case 2:
					GPIO_SetBits(GPIOA,GPIO_Pin_1);
					break;
			case 3:
				  GPIO_SetBits(GPIOA,GPIO_Pin_5);
					break;
			default:
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		}		
	}
}
