#ifndef DOUBLEBUFFER_H_
#define DOUBLEBUFFER_H_

#include "FreeRTOSIncludes.h"
#include "bmp.h"

typedef struct{
	BMP  bmp1;
	BMP  bmp2;
	BMP* toWrite;
	BMP* toRead;
	SemaphoreHandle_t readSemph;
	SemaphoreHandle_t writeSemph;
}DoubleBuffer;

extern DoubleBuffer doubleBuffer;

void DB_init();
BMP* DB_getBMPToRead();
BMP* DB_getBMPToWrite();
void DB_releaseBMPToRead();

#define DB_SWAP(pointer)\
	if((pointer) == &(doubleBuffer.bmp1)){\
			(pointer) = &(doubleBuffer.bmp2);\
	}else{\
			(pointer) = &(doubleBuffer.bmp1);\
	}

#endif /* DOUBLEBUFFER_H_ */
