#include "task_loader.h"
#include "FreeRTOSIncludes.h"
#include "bmp.h"

#include "doubleBuffer.h"

void task_loader(void* args){
	FATFS fatFs;
	FIL file;

	DB_init();
	while(f_mount(&fatFs, "", 1) != FR_OK);

	while(1){
		BMPError error;
		BMP* bmp;

		bmp = DB_getBMPToWrite();

		CHECK_ERROR(f_open(&file, "vane.bmp", FA_READ) != FR_OK);
		error = bmp_load(&file, bmp);
		CHECK_ERROR(error);
		f_close(&file);
	}
}
