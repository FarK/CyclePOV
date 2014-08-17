#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "defines.h"
#include "ff.h"
#include "bmp.h"

typedef struct{
	TCHAR path[MAX_PATH_LENGTH];
	unsigned int times;
}BMP_Frame;

typedef struct{
	BMP_Frame    frames[MAX_FRAMES];
	unsigned int nFrames;

	BMP_Frame*   currentFrame;
	BMP*         currentBMP;
	unsigned int timesCount;
}BMP_Animation;

extern BMP_Animation animation;

void incrementFrame(BMP_Frame* frame);

#endif /* ANIMATION_H_ */
