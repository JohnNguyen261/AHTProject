#include "delay.h"


//nhan k1 de timer bat dau dem, nhan k0 de thiet lap so lan nhan button... 

u8 k=0,i,solannhan=0,dem=1;

/*deklarasi struct*/
GPIO_InitTypeDef GPIO_InitStructure;


void init_GPIO(void);


/*---------------------------Interrupt Systick-------------------------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}


void init_GPIO()
{
	/*setting PORT Led*/
	/* enable GPIOA (PORT led)*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*setting PORT User Button*/
	/* enable GPIOE (PORT key)*/
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

    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;

    EXTI_Init(&EXTI_InitStruct);
 

    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;

    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x03;

    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;

    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}
 
void Configure_PE4(void) {

    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
    

    EXTI_InitStruct.EXTI_Line = EXTI_Line4;

    EXTI_InitStruct.EXTI_LineCmd = ENABLE;

    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;

    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;

    EXTI_Init(&EXTI_InitStruct);
 

    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;

    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;

    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;

    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}

void TIM_INT_Init()
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
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void EXTI3_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
        dem=0;
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)
				{
					k++;
				}
				
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}
void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
        dem=1;
				GPIO_ResetBits(GPIOA,GPIO_Pin_6);
			
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
				TIM_Cmd(TIM2, DISABLE);
        
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
void EXTI4_IRQHandler(void) {
    
    if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
        
        TIM_Cmd(TIM2, ENABLE);
				k=0;
        
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}


int main(){
	
	/*--------------------------Initialize Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	/*---------------Initialize Peripheral-----------------*/
	init_GPIO();																	/* Initialize GPIO					*/
	CLOCK_SetClockTo168MHz();
	Configure_PE3();
	Configure_PE4();
  TIM_INT_Init();																/* Initialize GPIO					*/
	while(1){
		while (1)
    {
			while (dem==1)
			{
				switch(k)
			{
					case 2: GPIO_ToggleBits(GPIOA,GPIO_Pin_7);delay_ms(1000);
									GPIO_ToggleBits(GPIOA,GPIO_Pin_7);delay_ms(1000);
									GPIO_ToggleBits(GPIOA,GPIO_Pin_7);delay_ms(1000);
					break;
					case 3:	GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
									GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
									GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
					break;
					case 4:	GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
									GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
									GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
					break;
					case 5:	GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
									GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
									GPIO_ToggleBits(GPIOA,GPIO_Pin_6);delay_ms(1000);
					break;
					case 6:	
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						break;
						case 7:	
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						break;
						case 8:	
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						break;
						case 9:	
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
						
						GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
						delay_ms(1000);
						break;
					default:
						GPIO_ResetBits(GPIOA,GPIO_Pin_6);
						GPIO_ResetBits(GPIOA,GPIO_Pin_7);
						break;			
			}
			}
    }
	}
}
