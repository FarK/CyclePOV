#include "task_led.h"

#include "FreeRTOSIncludes.h"
#include "bsp_led.h"
#include "stm32f4_discovery.h"
#include "defines.h"

void task_led(void* args){
	bsp_led_init();

	while(1){
		STM_EVAL_LEDToggle(LED6);
		vTaskDelay(MS_TO_TICKS(500));
	}
}
