#include "bsp_sensor.h"

#include "bikeInfo.h"
#include <tgmath.h>
#include "stm32f4xx_tim.h"

void bsp_sensor_init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	// GPIO CONFIG
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);

	// NVIC CONFIG
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x9;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// TIMER CONFIG
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// ADD TIMEBASE CONFIG
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(){
	uint32_t ticks;

	if(TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET){
		ticks = TIM_GetCapture1(TIM2);

		//Reconfigure timer
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		TIM_Cmd(TIM2, DISABLE);
		TIM_SetCounter(TIM2, 0);
		TIM_Cmd(TIM2, ENABLE);

		bikeInfo.period = ticks;
	}
}

float bsp_sensor_getAngle(){
	float time = TIM_GetCounter(TIM2);
	return (float)(time)/(float)(bikeInfo.period) * 2.0*M_PI;
}
