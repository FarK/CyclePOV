#include "bsp_userButton.h"

#include "stm32f4_discovery.h"

void bsp_userButton_init(){
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
}

void EXTI0_IRQHandler(){
	bsp_userButtonIRQ();
	EXTI_ClearITPendingBit(EXTI_Line0);
}
