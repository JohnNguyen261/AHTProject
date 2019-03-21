#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "delay.h"

u16 ngatgiu=0,ngatnhan=0,time=0,process=0;
u16 press=1,ngat,hold=2,status,k;
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

GPIO_InitTypeDef GPIO_InitStructure;

void init_GPIO(void);


/*---------------------------Interrupt Systick-------------------------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}



void init_GPIO()
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
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

void TIM2_INT_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1; //3s
    TIM_TimeBaseInitStruct.TIM_Period = 29999; //3s
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM2, DISABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x03;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

void TIM3_INT_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 840-1; //1ms
    TIM_TimeBaseInitStruct.TIM_Period = 99; //1ms
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM3, DISABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

/*void TIM4_INT_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1; //500ms
    TIM_TimeBaseInitStruct.TIM_Period = 4999; //500ms
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM4, DISABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}*/

void EXTI3_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line3) != RESET)
			{
				ngatgiu++;
				ngatnhan++;
				if(ngatgiu==1)
				{
					TIM_Cmd(TIM3, ENABLE);
					TIM_Cmd(TIM2, ENABLE);
					process=0;
					k=0;
				}
				if(ngatgiu==2)
				{
					TIM_Cmd(TIM3, DISABLE);
					time=process;
					ngatgiu=0;
				}
			}
        EXTI_ClearITPendingBit(EXTI_Line3);
}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
        //GPIO_ResetBits(GPIOA,GPIO_Pin_7);
				//GPIO_ResetBits(GPIOA,GPIO_Pin_6);
				TIM_Cmd(TIM2, DISABLE);
				k=ngatnhan;
        ngatnhan=0;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void TIM3_IRQHandler()
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
			process++;  
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

/*void TIM4_IRQHandler()
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update))
    {
        if(solanngat==1)
				{
					status=hold;
				}
				if(solanngat>1)
				{
					status=press;
				}
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}*/

int main(){
	init_Clock();
	/*--------------------------Initialize Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	/*---------------Initialize Peripheral-----------------*/
	init_GPIO();																	/* Initialize GPIO					*/
	Configure_PE3();
	TIM2_INT_Init();
	TIM3_INT_Init();
	//TIM4_INT_Init();
	
	
	while(1){
		//if(status==hold)
		//{
		while(k!=0&&time!=0)
			{
				if(time<2000) //mode 1 giu button be hon 2s tat led
				{
					GPIO_SetBits(GPIOA,GPIO_Pin_6);
					GPIO_SetBits(GPIOA,GPIO_Pin_7);
				}
				if(time>2000) //mode 2 giu nhieu hon 2s chop tat 2led
				{
					GPIO_SetBits(GPIOA,GPIO_Pin_6);
					GPIO_SetBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
					GPIO_ResetBits(GPIOA,GPIO_Pin_6);
					GPIO_ResetBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
					GPIO_SetBits(GPIOA,GPIO_Pin_6);
					GPIO_SetBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
					GPIO_ResetBits(GPIOA,GPIO_Pin_6);
					GPIO_ResetBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
					GPIO_SetBits(GPIOA,GPIO_Pin_6);
					GPIO_SetBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
					GPIO_ResetBits(GPIOA,GPIO_Pin_6);
					GPIO_ResetBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
				}	
				if(k<=6&&k>2) // nhan tu 2 den 3 lan mode 3 chop tat led 2
				{
					GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
					delay_ms(200);
					GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
					delay_ms(200);
					GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
					delay_ms(200);
				}
				if(k>6) // nhan hon 3 lan mod 4 chop tat led 3
				{
					GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
					GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
					GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
					delay_ms(200);
				}
			}
	}	
}
