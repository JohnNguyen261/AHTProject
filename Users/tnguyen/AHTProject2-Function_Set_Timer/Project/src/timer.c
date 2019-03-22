//void Timer4_Init()
//{
//    // Enable clock for TIM4
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//    // TIM2 initialization overflow every 500ms
//    // TIM2 by default has clock of 84MHz
//    // Here, we must set value of prescaler and period,
//    // so update event is 0.5Hz or 500ms
//    // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * 
//    // (TIM_Period + 1))
//    // Update Event (Hz) = 84MHz / ((4199 + 1) * (9999 + 1)) = 2 Hz
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//    TIM_TimeBaseInitStruct.TIM_Prescaler = 8399;
//    TIM_TimeBaseInitStruct.TIM_Period = 49999;  // 1/5Hz # 5 seconds
//    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

//    // TIM4 initialize
//    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
//    // Enable TIM2 interrupt
//    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
//    // Start TIM4
//    TIM_Cmd(TIM4, DISABLE);
//    //TIM_Cmd(TIM4, ENABLE);
//    // Nested vectored interrupt settings
//    // TIM2 interrupt is most important (PreemptionPriority and 
//    // SubPriority = 0)
//    NVIC_InitTypeDef NVIC_InitStruct;
//    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
//    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStruct);
//}
//    //After that, we must write code for interrupt handler that will be call every timer interrupt (500ms)
//    //In this handler, we write code for toggle LED.
//void TIM4_IRQHandler()
//{
//    // Checks whether the TIM2 interrupt has occurred or not
//    if (TIM_GetITStatus(TIM4, TIM_IT_Update))
//    {
//     	TIM_Cmd(TIM4, DISABLE);
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//    }
//}
/****************************************************************************************************************************************/
#include "timer.h"
#include "string.h"
#include "stdio.h"
void Set_Timer(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t Period )
{
char t1[] = "RCC_APB1Periph_";
char t2[] = "TIMx";
char t3[] = "_IRQn";

strcat(t1, t2);
strcat(t2, t3);
RCC_APB1PeriphClockCmd(t1, ENABLE);
//Here, we must set value of prescaler and period,
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
TIM_TimeBaseInitStruct.TIM_Prescaler = Prescaler;
TIM_TimeBaseInitStruct.TIM_Period = Period; 
TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
// TIM4 initialize
TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);
// Enable TIM2 interrupt
TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
// Start TIM4
TIM_Cmd(TIMx, ENABLE);
 // Nested vectored interrupt settings
//    // TIM2 interrupt is most important (PreemptionPriority and 
//    // SubPriority = 0)
NVIC_InitTypeDef NVIC_InitStruct;
NVIC_InitStruct.NVIC_IRQChannel = t2;
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStruct);

}
