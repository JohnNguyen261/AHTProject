#include "delay.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"


u32 step=1999;
unsigned int duty=0;
void USART_Config(void)
{
    // Enable clock for GPIOB
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    // Enable clock for USART1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // Connect PB6 to USART1_Tx
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    // Connect PB7 to USART1_Rx
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    // Initialization of GPIOB
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Initialization of USART1
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl =
            USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);

    // Enable USART1
    USART_Cmd(USART1, ENABLE);
}

void USART_PutChar(char c)
{
    // Wait until transmit data register is empty
    while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
    // Send a char using USART1
    USART_SendData(USART1, c);
}

void USART_PutString(char *s)
{
    // Send a string
    while (*s)
    {
        USART_PutChar(*s++);
    }
}

uint16_t USART_GetChar()
{
    // Wait until data is received
    while (!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
    // Read received char
    return USART_ReceiveData(USART1);
}




/*deklarasi struct*/
GPIO_InitTypeDef GPIO_InitStructure;

/*deklarasi fungsi*/
void init_GPIO(void);


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

void TM_TIMER_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_BaseStruct.TIM_Prescaler = 0;

    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_BaseStruct.TIM_Period = 9999; /* 8400kHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_BaseStruct);

}
 
void TM_PWM_Init(void) {
    TIM_OCInitTypeDef TIM_OCStruct;

    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    
    TIM_OCStruct.TIM_Pulse = duty; 
    TIM_OC1Init(TIM3, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    
    TIM_OCStruct.TIM_Pulse = duty; 
    TIM_OC2Init(TIM3, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
		TIM_ARRPreloadConfig(TIM3, ENABLE);
		TIM_Cmd(TIM3, ENABLE);
		
}


int main(void)
{
		init_Clock();
		TM_TIMER_Init();
		TM_PWM_Init();
	
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

    // Call USART1 configuration
    USART_Config();

    // Send "Hello, World!" to PC
    USART_PutString("Hello, World!\n");
    while (1)
    {
        // Get a char from PC
        uint16_t data = USART_GetChar();
				if (data == 'B')
        {
						duty=9999;
				}
				if (data == 'T')
        {
					duty=0;
				}
        if (data == 'H')
        {
					duty=duty+step;
					if(duty>10000)
					{
						duty=0;
					}
        }
        if (data == 'L')
        {
					duty=duty-step;
					if(duty<5)
					{
						duty=9999;
					}
        }
				TIM3->CCR1 = duty;
				TIM3->CCR2 = duty;
    }
}
