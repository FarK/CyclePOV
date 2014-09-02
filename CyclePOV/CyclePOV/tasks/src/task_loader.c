#include "task_loader.h"
#include "FreeRTOSIncludes.h"

#include "doubleBuffer.h"
#include "parser.h"
#include "animation.h"

void task_loader(void* args){
	FATFS fatFs;
	FIL file;
	BMP_Frame* frameToLoad;

	//Init double buffer
	DB_init();

	//Mount SD
	while(f_mount(&fatFs, "", 1) != FR_OK);

	//Init animation index
	CHECK_ERROR(f_open(&file, INDEX_FILE, FA_READ) != FR_OK);
	parseIndex(&file);
	animation.currentFrame = &animation.frames[0];
	animation.currentBMP = doubleBuffer.toRead;
	DB_SWAP(doubleBuffer.toRead);
	animation.timesCount = 0;
	frameToLoad = &animation.frames[0];

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
