#include "bsp_switches.h"
#include "stm32f4xx.h"

const uint8_t swXToSwitchState[2][2] = {   //Sw1 Sw2
	{BOTH_STRIPES,                         // 0   0
	 FIRST_STRIPES},                       // 0   1
	{INVALID,                              // 1   0
	 LAST_STRIPES},                        // 1   1
};

void readSwitches(uint8_t* sw1, uint8_t* sw2);

void bsp_switches_init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	uint8_t sw1, sw2;

	// Enable Clocks
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// Configure GPIOs as input
	GPIO_StructInit(&GPIO_InitStructure);
	//Switch 1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//Switch 2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	 // Connect EXTI lines to GPIO pins
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource8);	//Switch 1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource10);	//Switch 2

	// Configure EXTI lines
	EXTI_StructInit(&EXTI_InitStructure);
	//Switch 1
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//Switch 2
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	// Enable and set EXTI interrupt
	//Switch 1
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0E;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//Switch 1
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0E;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//Init switches status
	readSwitches(&sw1, &sw2);
	bsp_switchesIRQ(sw1, sw2);
}

void EXTI9_5_IRQHandler(){
	uint8_t sw1,sw2;

	if(EXTI_GetITStatus(EXTI_Line8) == SET){
		readSwitches(&sw1, &sw2);
		bsp_switchesIRQ(sw1, sw2);
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}

void EXTI15_10_IRQHandler(){
	uint8_t sw1,sw2;

	if(EXTI_GetITStatus(EXTI_Line10) == SET){
		readSwitches(&sw1, &sw2);
		bsp_switchesIRQ(sw1, sw2);
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}

void readSwitches(uint8_t* sw1, uint8_t* sw2){
	*sw1 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8);
	*sw2 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10);
}
