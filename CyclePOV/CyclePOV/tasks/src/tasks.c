#include "tasks.h"

#include "FreeRTOSIncludes.h"
#include "stddef.h"
#include "projdefs.h"

//Tasks includes
#include "task_idle.h"
#include "task_loader.h"

void createTasks(){

	configASSERT(xTaskCreate(
		task_idle,
		"idle",
		configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY,
		(TaskHandle_t*)NULL
	));

	configASSERT(xTaskCreate(
		task_loader,
		"loader",
		1024*2,
		NULL,
		tskIDLE_PRIORITY+1,
		(TaskHandle_t*)NULL
	));
}
