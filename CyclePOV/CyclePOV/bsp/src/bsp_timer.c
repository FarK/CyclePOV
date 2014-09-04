#include "bsp_timer.h"

#include "stm32f4xx_tim.h"

void bsp_timer_init(){
	//NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	// NVIC CONFIG
	/*NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x9;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);*/

	// TIMER CONFIG
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	// ADD TIMEBASE CONFIG
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	//TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
//	TIM_InternalClockConfig(TIM5);

	//TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM5, ENABLE);
}

/* Returns the time in ticks */
uint32_t bsp_timer_getTime(){
	return TIM_GetCounter(TIM5);
}
