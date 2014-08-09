#include "bsp_ledsButton.h"

#include "stm32f4_discovery.h"

void bsp_ledsButton_init(){
	//Init LEDs
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);

	//Init User button (blue)
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
}

void EXTI0_IRQHandler(){
	ISR_ledsButton();
	EXTI_ClearITPendingBit(EXTI_Line0);
}
