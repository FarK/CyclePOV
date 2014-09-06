#include "bikeInfo.h"

#include <tgmath.h>
#include <stdint.h>
#define PI M_PI

BikeInfo bikeInfo;
Stripes stripes;

void bikeInfo_init(){
	bikeInfo.wheelRadius = MAX_WHEEL_RADIUS;
	bikeInfo.edgeRadius = MAX_EDGE_RADIUS;
	bikeInfo.stripeLength = MAX_STRIPE_LENGTH;

	stripes.numLeds = 0;
	stripes.numStripes = 8;
	stripes.starStripe = &stripes.stripes[0];
	stripes.endStripe = &stripes.stripes[7];

	stripes.stripes[0].angle = 0.0 + SENSOR_ANGLE;
	stripes.stripes[0].numLeds = 36;
	stripes.stripes[0].startLed = 0;
	stripes.stripes[0].endLed = 35;

	stripes.stripes[1].angle = 3.0/2.0*PI + SENSOR_ANGLE;
	stripes.stripes[1].numLeds = 36;
	stripes.stripes[1].startLed = 0;
	stripes.stripes[1].endLed = 35;

	stripes.stripes[2].angle = PI + SENSOR_ANGLE;
	stripes.stripes[2].numLeds = 36;
	stripes.stripes[2].startLed = 1;
	stripes.stripes[2].endLed = 35;

	stripes.stripes[3].angle = PI/2.0 + SENSOR_ANGLE;
	stripes.stripes[3].numLeds = 36;
	stripes.stripes[3].startLed = 0;
	stripes.stripes[3].endLed = 35;


	stripes.stripes[4].angle = PI/4.0 + SENSOR_ANGLE;
	stripes.stripes[4].numLeds = 15;
	stripes.stripes[4].startLed = 1;
	stripes.stripes[4].endLed = 14;

	stripes.stripes[5].angle = 7*PI/4.0 + SENSOR_ANGLE;
	stripes.stripes[5].numLeds = 15;
	stripes.stripes[5].startLed = 0;
	stripes.stripes[5].endLed = 13;

	stripes.stripes[6].angle = 5*PI/4.0 + SENSOR_ANGLE;
	stripes.stripes[6].numLeds = 15;
	stripes.stripes[6].startLed = 1;
	stripes.stripes[6].endLed = 14;

	stripes.stripes[7].angle = 3*PI/4.0 + SENSOR_ANGLE;
	stripes.stripes[7].numLeds = 15;
	stripes.stripes[7].startLed = 0;
	stripes.stripes[7].endLed = 13;

	bikeInfo.period = UINT32_MAX; //Avoids division by 0

	//Calculate number of LEDs
	unsigned int s;
	Stripe* stripe;

	for(s=0, stripe=&stripes.stripes[0];
		s<stripes.numStripes;
		++s, ++stripe)
	{
		stripes.numLeds += stripe->numLeds;
	}
}
