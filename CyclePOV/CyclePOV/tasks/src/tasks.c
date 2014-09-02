#include "tasks.h"

#include "FreeRTOSIncludes.h"
#include "stddef.h"
#include "projdefs.h"

//Tasks includes
#include "task_idle.h"
#include "task_loader.h"
#include "task_ledsStripes.h"

void createTasks(){
	//Semaphore for wait loader initialization
	endLoaderInitSemph = xSemaphoreCreateBinary();

	configASSERT(xTaskCreate(
		task_idle,
		"idle",
		IDLE_STACK_SIZE,
		NULL,
		IDLE_PRIORITY,
		(TaskHandle_t*)NULL
	));

	configASSERT(xTaskCreate(
		task_loader,
		"loader",
		LOADER_STACK_SIZE,
		NULL,
		LOADER_PRIORITY,
		(TaskHandle_t*)NULL
	));

	configASSERT(xTaskCreate(
		task_ledsStripes,
		"ledsStripes",
		LEDS_STRIPE_STACK_SIZE,
		NULL,
		LEDS_STRIPE_PRIORITY,
		(TaskHandle_t*)NULL
	));
}
