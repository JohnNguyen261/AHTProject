// Nhan KEY1 buong ra ngay trong vong 200ms thi tang/giam do sang 300
// Nhan KEY1 giu luon thi led sang dan hoac toi dan

#include "stm32f4xx.h"
#include "delay.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

int n=0, m=0;
int a=0;
int PushButton=0;
void SysTick_Handler(){
     TimingDelay_Decrement();
}
void TM_LEDS_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /* Clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
 
    /* Alternating functions for pins */
      GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
//    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
//    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
//    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
    
    /* Set pins */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;// | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void TM_TIMER_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    
    /* Enable clock for TIM4 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
/*    
    TIM4 is connected to APB1 bus, which has on F407 device 42MHz clock                 
    But, timer has internal PLL, which double this frequency for timer, up to 84MHz     
    Remember: Not each timer is connected to APB1, there are also timers connected     
    on APB2, which works at 84MHz by default, and internal PLL increase                 
    this to up to 168MHz                                                             
    
    Set timer prescaller 
    Timer count frequency is set with 
    
    timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)        
    
    In our case, we want a max frequency for timer, so we set prescaller to 0         
    And our timer will have tick frequency        
    
    timer_tick_frequency = 84000000 / (0 + 1) = 84000000 
*/    
    TIM_BaseStruct.TIM_Prescaler = 0; /* 16kHz PWM */
    /* Count up */
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
/*
    Set timer period when it have reset
    First you have to know max value for timer
    In our case it is 16bit = 65535
    To get your frequency for PWM, equation is simple
    
    PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
    
    If you know your PWM frequency you want to have timer period set correct
    
    TIM_Period = timer_tick_frequency / PWM_frequency - 1
    
    In our case, for 10Khz PWM_frequency, set Period to
    
    TIM_Period = 84000000 / 10000 - 1 = 8399
    
    If you get TIM_Period larger than max timer value (in our case 65535),
    you have to choose larger prescaler and slow down timer tick frequency
*/
    TIM_BaseStruct.TIM_Period = 5249; /* 16kHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    /* Initialize TIM4 */
    TIM_TimeBaseInit(TIM2, &TIM_BaseStruct);
    /* Start count on TIM4 */
    TIM_Cmd(TIM2, ENABLE);
}
 
void TM_PWM_Init(int n) {
    TIM_OCInitTypeDef TIM_OCStruct;
    
    /* Common settings */
    
    /* PWM mode 2 = Clear on compare match */
    /* PWM mode 1 = Set on compare match */
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
    
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
//    TIM_OCStruct.TIM_Pulse = 2099; /* 25% duty cycle */
//    TIM_OC1Init(TIM2, &TIM_OCStruct);
//    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    
    TIM_OCStruct.TIM_Pulse = n; /* 50% duty cycle */
    TIM_OC2Init(TIM2, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    
//    TIM_OCStruct.TIM_Pulse = 6299; /* 75% duty cycle */
//    TIM_OC3Init(TIM2, &TIM_OCStruct);
//    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
//    
//    TIM_OCStruct.TIM_Pulse = 8399; /* 100% duty cycle */
//    TIM_OC4Init(TIM2, &TIM_OCStruct);
//    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
}

 void Clock_Init(){
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

void Key1_PE3_Interrupt(void){
	
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
    
    /* Tell system that you will use PE3 for EXTI_Line4 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
    
    /* PE3 is connected to EXTI_Line3 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line3;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
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
void EXTI3_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
        /* Do your stuff when PE4 is changed */
        a=0;
			  PushButton=0;
			  PushButton++;
        TIM_Cmd(TIM3, ENABLE);			
        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}
/* Init Timer 3*/
void TIM_Init(){
    // Enable clock for TIM3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // TIM2 initialization overflow every 500ms
    // TIM2 by default has clock of 84MHz
    // Here, we must set value of prescaler and period,
    // so update event is 0.5Hz or 500ms
    // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * 
    // (TIM_Period + 1))
    // Update Event (Hz) = 84MHz / ((4199 + 1) * (9999 + 1)) = 2 Hz
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 4199;
    TIM_TimeBaseInitStruct.TIM_Period = 3999;//0.2s
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // TIM2 initialize
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    // Start TIM2
    TIM_Cmd(TIM3, DISABLE);

    // Nested vectored interrupt settings
    // TIM2 interrupt is most important (PreemptionPriority and 
    // SubPriority = 0)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
/* Ngat TIM3*/
void TIM3_IRQHandler(){
    // Checks whether the TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
        if((PushButton>0)&&(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==1)) a=1;
			  else if ((PushButton>0)&&(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0)) a=2;
			  
			  TIM_Cmd(TIM3, DISABLE);
       	
        // Clears the TIM2 interrupt pending bit
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
/*Led tang hoac giam do sang 300 sau moi lan nhan nut hoac sau System_Tick delay_ms() neu nhan giu nut*/
void Led_Inc_Dec(void){ 
if ((n>0)&&(m==0))
			 {	 
				 n-=300;
			 }
			 else if ((n<=1)&&(m==0))
			 {
				m=1;
				n+=300;
			 }
			 else if ((n<5249)&&(m==1)) //n=5249 Duty Cycle for PWM 16KHz
			 {
				 n+=300;
			 }
			 else if (n>=5249)
			 {
				 m=0;
			 }
 if (a==1) a=0;
}
	

int main(void) 
{
Clock_Init(); 
  if (SysTick_Config(SystemCoreClock / 1000))  /* SysTick 1 msec interrupts  */
  {  while (1); }                               /* Capture error              */
Key1_PE3_Interrupt();
EXTI3_IRQHandler();
TM_LEDS_Init();
TM_TIMER_Init();
TIM_Init();
TIM3_IRQHandler();   
    while (1) 
		{
		  if (a==1) Led_Inc_Dec();
			if ((a==2)&&(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0)) Led_Inc_Dec();
			delay_ms(150);
		  TM_PWM_Init(n);
		}
}


