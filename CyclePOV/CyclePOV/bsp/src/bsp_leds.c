#include "bsp_leds.h"

#include "stm32f4_discovery.h"

const Led_TypeDef ledsOrdered[4] = {LED3,LED5,LED6,LED4};

void bsp_leds_init(){
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	STM_EVAL_LEDInit(LED7);
}

void bsp_leds_round(){
	//static Led_TypeDef nextLed = LED3;
	static unsigned int nextLed = 0;

	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);

	STM_EVAL_LEDOn(ledsOrdered[nextLed++]);
	if(nextLed >= 4) nextLed = 0;
}

void bsp_leds_toggle(){
	STM_EVAL_LEDToggle(LED3);
	STM_EVAL_LEDToggle(LED4);
	STM_EVAL_LEDToggle(LED5);
	STM_EVAL_LEDToggle(LED6);
}

void bsp_leds_on(){
	STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOn(LED4);
	STM_EVAL_LEDOn(LED5);
	STM_EVAL_LEDOn(LED6);
}

void bsp_leds_off(){
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);
}

void bsp_leds_toggleIdleLed(){
	STM_EVAL_LEDToggle(LED7);
}
