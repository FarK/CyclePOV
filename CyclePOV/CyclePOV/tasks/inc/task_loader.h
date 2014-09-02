#ifndef TASK_LOADER_H_
#define TASK_LOADER_H_

#include "bmp.h"
#include "FreeRTOSIncludes.h"

void task_loader(void* args);
BMP* getNextFrame();

extern SemaphoreHandle_t endLoaderInitSemph;

#endif /* TASK_LOADER_H_ */
