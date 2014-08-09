#include "bsp_led.h"

#include "stm32f4_discovery.h"

void bsp_led_init(){
	//Init LED
	STM_EVAL_LEDInit(LED6);
}
