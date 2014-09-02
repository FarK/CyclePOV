#include "task_loader.h"
#include "FreeRTOSIncludes.h"

#include "doubleBuffer.h"
#include "parser.h"
#include "animation.h"

void task_loader(void* args){
	FATFS fatFs;
	FIL file;
	BMP_Frame* frameToLoad;

	//Init double buffer and animation
	animation.timesCount = 0;
	animation.timesCount = 0;
	DB_init();
	animation.currentFrame = &animation.frames[0];
	animation.currentBMP = doubleBuffer.toRead;
	frameToLoad = &animation.frames[0];
	animation.timesCount = 0;
	animation.currentFrame->times = 0;	//Force DB_getBMPToRead() on init in getNextFrame()

	//Mount SD
	while(f_mount(&fatFs, "", 1) != FR_OK);

	//Init animation index
	CHECK_ERROR(f_open(&file, INDEX_FILE, FA_READ) != FR_OK);
	parseIndex(&file);


	//Task start
	while(1){
		BMPError error;
		BMP* bmp;

		bmp = DB_getBMPToWrite();

		CHECK_ERROR(f_open(&file, frameToLoad->path, FA_READ) != FR_OK);
		error = bmp_load(&file, bmp);
		CHECK_ERROR(error);
		f_close(&file);

		frameToLoad = incrementedFrame(frameToLoad);

		DB_releaseBMPToRead();
	}
}

BMP* getNextFrame(){
	++animation.timesCount;

	if(animation.timesCount >= animation.currentFrame->times){
		animation.currentBMP = DB_getBMPToRead();
		animation.currentFrame = incrementedFrame(animation.currentFrame);
		animation.timesCount = 0;
	}

	return animation.currentBMP;
}
