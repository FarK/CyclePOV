#include "task_idle.h"

#include "FreeRTOSIncludes.h"
#include "stm32f4_discovery.h"
#include "bsp_leds.h"
#include "defines.h"

void task_idle(void* args){
	bsp_leds_init();

	while(1){
		bsp_leds_toggleIdleLed();
		vTaskDelay(MS_TO_TICKS(500));
	}
}
