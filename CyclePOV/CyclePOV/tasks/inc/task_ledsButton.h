#ifndef TASK_LEDSBUTTON_H_
#define TASK_LEDSBUTTON_H_

#include "FreeRTOSIncludes.h"

extern SemaphoreHandle_t semaphore;

void task_ledsButton(void* args);

#endif /* TASK_LEDSBUTTON_H_ */
