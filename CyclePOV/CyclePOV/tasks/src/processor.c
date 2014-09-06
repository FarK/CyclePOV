#include "processor.h"

#include "defines.h"
#include "bikeInfo.h"
#include <tgmath.h>

#define PI2 (2.0*M_PI)


typedef struct{
	uint32_t norm;
	uint8_t size;
	uint8_t center;
}Mask;

Mask mask;
DWORD imgCenter_x, imgCenter_y;
float pxPerCm;
float pxPerStripe;

//Aux private function
void setMask(BMP* bmp, float pixelsPerLED);
void convolution(DWORD cx, DWORD cy, LED* led, BMP* bmp);

void process(float dangle, BMP* bmp){
	float a,r;	//angle  (a) and module (r)
	float cosa,sina;
	float pixelsPerLED;
	float edge_px = bikeInfo.edgeRadius*pxPerCm;
	DWORD px,py;
	Stripe* stripe;
	uint8_t l;

	for(stripe=stripes.starStripe ;
	    stripe<=stripes.endStripe ;
	    ++stripe)
	{
		//Precalculate:
		pixelsPerLED = pxPerStripe/(stripe->numLeds-1);
		a = stripe->angle + dangle;
		cosa = cos(a);
		sina = sin(a);

		setMask(bmp, pixelsPerLED);

		for(l=stripe->startLed ; l<=stripe->endLed ; ++l){
			//Led module
			r = edge_px + l*pixelsPerLED;

			//Calculate image coordinates
			px = r*cosa + imgCenter_x;
			py = r*sina + imgCenter_y;

			//Apply mask
			convolution(px,py, &stripe->leds[l], bmp);
		}
	}
}

void processConfig(BMP* bmp){
	DWORD imgSize;

	imgCenter_x = bmp->arrayInfo.Width/2;
	imgCenter_y = bmp->arrayInfo.Height/2;

	if(bmp->arrayInfo.Width <= bmp->arrayInfo.Height)
		imgSize = bmp->arrayInfo.Width;
	else
		imgSize = bmp->arrayInfo.Height;

	pxPerCm = ((float)(imgSize))/(2.0*bikeInfo.wheelRadius);
	pxPerStripe = bikeInfo.stripeLength*pxPerCm;
}

void setMask(BMP* bmp, float pixelsPerLED){
	//Set odd size
	mask.size = pixelsPerLED;
	mask.size += mask.size%2? 0 : 1;

	mask.center = mask.size/2;
	mask.norm = mask.size*mask.size;
}

void convolution(DWORD cx, DWORD cy, LED* led, BMP* bmp){
	DWORD i,j;
	DWORD_S px,py;
	DWORD_S Width = bmp->arrayInfo.Width;
	DWORD_S Height = bmp->arrayInfo.Height;
	BYTE* bmpPixel;
	uint32_t auxLED[3] = {0,0,0};

	//Difference between image center and mask center
	DWORD dx = cx - mask.center;
	DWORD dy = cy + mask.center;

	for(i=0 ; i<mask.size ; ++i){
		for(j=0 ; j<mask.size ; ++j){
			//Mask coordinates to image coordinates
			px = dx + i;
			py = dy - j;
			//Mirror limits
			if(px >= Width)  px = (Width-1) - (px-Width);
			else if(px < 0)  px = -px;
			if(py >= Height) py = (Height-1) - (py-Height);
			else if(py < 0)  py = -py;

			//Accumulates values
			bmpPixel = bmp_getPixel(px, py, bmp);
			auxLED[0] += bmpPixel[0];
			auxLED[1] += bmpPixel[1];
			auxLED[2] += bmpPixel[2];
		}
	}

	//Normalize. Note: RGB is changed to BGR
	(*led)[1] = auxLED[0]/mask.norm;
	(*led)[2] = auxLED[1]/mask.norm;
	(*led)[0] = auxLED[2]/mask.norm;
}
