#include "bikeInfo.h"

#include <tgmath.h>
#include <float.h>
#define PI M_PI

BikeInfo bikeInfo;

void bikeInfo_init(){
	bikeInfo.wheelRadius = MAX_WHEEL_RADIUS;
	bikeInfo.edgeRadius = MAX_EDGE_RADIUS;
	bikeInfo.stripeLength = MAX_STRIPE_LENGTH;
	bikeInfo.numLeds = 0;

	bikeInfo.stripes.numStripes = 8;

	bikeInfo.stripes.stripes[0].angle = 0.0;
	bikeInfo.stripes.stripes[0].numLeds = 36;

	bikeInfo.stripes.stripes[1].angle = 3.0/2.0*PI;
	bikeInfo.stripes.stripes[1].numLeds = 36;

	bikeInfo.stripes.stripes[2].angle = PI;
	bikeInfo.stripes.stripes[2].numLeds = 36;

	bikeInfo.stripes.stripes[3].angle = PI/2.0;
	bikeInfo.stripes.stripes[3].numLeds = 36;

	bikeInfo.stripes.stripes[4].angle = 7*PI/4.0;
	bikeInfo.stripes.stripes[4].numLeds = 14;

	bikeInfo.stripes.stripes[5].angle = PI/4.0;
	bikeInfo.stripes.stripes[5].numLeds = 14;

	bikeInfo.stripes.stripes[6].angle = 3*PI/4.0;
	bikeInfo.stripes.stripes[6].numLeds = 14;

	bikeInfo.stripes.stripes[7].angle = 5*PI/4.0;
	bikeInfo.stripes.stripes[7].numLeds = 14;

	bikeInfo.period = FLT_MAX; //Avoids division by 0

	//Calculate number of LEDs
	unsigned int s;
	Stripes* stripes = &bikeInfo.stripes;
	Stripe* stripe;

	for(s=0, stripe=&stripes->stripes[0];
		s<stripes->numStripes;
		++s, ++stripe)
	{
		bikeInfo.numLeds += stripe->numLeds;
	}
}
