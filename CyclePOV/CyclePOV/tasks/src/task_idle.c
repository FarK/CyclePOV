#include "task_idle.h"

#include "FreeRTOSIncludes.h"
#include "stm32f4_discovery.h"
#include "bsp_idle.h"
#include "defines.h"

void task_idle(void* args){
	bsp_idle_init();

	while(1){
		STM_EVAL_LEDToggle(LED7);
		vTaskDelay(MS_TO_TICKS(500));
	}
}
