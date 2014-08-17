#include "animation.h"

BMP_Animation animation;

/* Increments frame in loop */
void incrementFrame(BMP_Frame* frame){
	if(frame == &animation.frames[animation.nFrames-1])
		frame = &animation.frames[0];
	else
		++frame;
}
