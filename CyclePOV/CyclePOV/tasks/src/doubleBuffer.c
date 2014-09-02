#include "doubleBuffer.h"

DoubleBuffer doubleBuffer;

void DB_init(){
	doubleBuffer.writeSemph = xSemaphoreCreateCounting(2,2);
	doubleBuffer.readSemph = xSemaphoreCreateCounting(2,0);
	doubleBuffer.toWrite = &doubleBuffer.bmp1;
	doubleBuffer.toRead = &doubleBuffer.bmp1;
}

BMP* DB_getBMPToRead(){
	BMP* bmp;

	ASSERT(xSemaphoreTake(doubleBuffer.readSemph, portMAX_DELAY));
	ASSERT(xSemaphoreGive(doubleBuffer.writeSemph));

	bmp = doubleBuffer.toRead;
	DB_SWAP(doubleBuffer.toRead);

	return bmp;
}

BMP* DB_getBMPToWrite(){
	BMP* bmp;

	ASSERT(xSemaphoreTake(doubleBuffer.writeSemph, portMAX_DELAY));

	bmp = doubleBuffer.toWrite;
	DB_SWAP(doubleBuffer.toWrite);

	return bmp;
}

/* Release the buffer */
void DB_releaseBMPToRead(){
	ASSERT(xSemaphoreGive(doubleBuffer.readSemph));
}
