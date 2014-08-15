#include "task_loader.h"
#include "bsp_loader.h"
#include "FreeRTOSIncludes.h"
#include "bmp.h"

#include "defines.h"
#include "stm32f4_discovery.h"

FATFS fatFs;
FIL file;
BMP bmp;
BMP bmp2;

void task_loader(void* args){
	BMPError error;
	float time = TICKS_TO_MS(xTaskGetTickCount());

	bsp_loader_init();

	while(f_mount(&fatFs, "", 1) != FR_OK);

	CHECK_ERROR(f_open(&file, "vane.bmp", FA_READ) != FR_OK);
	error = bmp_load(&file, &bmp);
	CHECK_ERROR(error);
	f_close(&file);

	time = TICKS_TO_MS(xTaskGetTickCount()) - time;

	CHECK_ERROR(f_open(&file, "vane.bmp", FA_READ) != FR_OK);
	error = bmp_load(&file, &bmp2);
	CHECK_ERROR(error);
	f_close(&file);

	STM_EVAL_LEDOn(LED3);

	while(1);
}
