#include "tasks.h"

#include "FreeRTOSIncludes.h"
#include "stddef.h"
#include "projdefs.h"

//Tasks includes
#include "task_ledsButton.h"
#include "task_led.h"
#include "task_idle.h"

void createTasks(){
	configASSERT(xTaskCreate(
		task_ledsButton,
		"LEDs",
		configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 1,
		(TaskHandle_t*)NULL
	));

	configASSERT(xTaskCreate(
		task_led,
		"button",
		configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY+1,
		(TaskHandle_t*)NULL
	));

	configASSERT(xTaskCreate(
		task_idle,
		"idle",
		configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY,
		(TaskHandle_t*)NULL
	));
}
