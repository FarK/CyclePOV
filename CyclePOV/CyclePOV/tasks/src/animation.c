#include "animation.h"

BMP_Animation animation;

/* Increments frame in loop */
BMP_Frame* incrementedFrame(BMP_Frame* frame){
	if(frame == &animation.frames[animation.nFrames-1])
		return &animation.frames[0];
	else
		return ++frame;
}
