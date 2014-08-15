#include "task_ledsButton.h"

#include "FreeRTOSIncludes.h"
#include "bsp_ledsButton.h"
#include "stm32f4_discovery.h"
#include "portmacro.h"

SemaphoreHandle_t semaphore;

void task_ledsButton(void* args){
	bsp_ledsButton_init();

	semaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(semaphore);

	while(1){
		configASSERT(xSemaphoreTake(semaphore, portMAX_DELAY));

		//STM_EVAL_LEDToggle(LED3);
		STM_EVAL_LEDToggle(LED4);
		STM_EVAL_LEDToggle(LED5);
	}
}

//Interrupt handler
void ISR_ledsButton(){
	BaseType_t higherPriorityTaskWoken;
	//configASSERT(xSemaphoreGiveFromISR(semaphore, &higherPriorityTaskWoken));
	xSemaphoreGiveFromISR(semaphore, &higherPriorityTaskWoken);
	portEND_SWITCHING_ISR(higherPriorityTaskWoken);
}
