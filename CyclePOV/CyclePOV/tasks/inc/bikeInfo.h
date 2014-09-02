#ifndef BIKEINFO_H_
#define BIKEINFO_H_

#include <stdint.h>

#define MAX_WHEEL_RADIUS	27.5	//Radius wheel in cm
#define MAX_EDGE_RADIUS		3.5		//Edge radius in cm
#define MAX_STRIPE_LENGTH	(MAX_WHEEL_RADIUS - MAX_EDGE_RADIUS)
#define MAX_NUM_LEDS		36		//Max number of LEDs in the stripe
#define MIN_NUM_LEDS		14		//Min number of LEDs in the stripe
#define MAX_NUM_STRIPES		8		//Max number of LEDs stripes

typedef uint8_t LED[3];

typedef struct{
	LED leds[MAX_NUM_LEDS];
	uint8_t numLeds;
	float angle;	//Stripe angle in rad
}Stripe;

typedef struct{
	Stripe stripes[MAX_NUM_STRIPES];
	uint8_t numStripes;
}Stripes;

typedef struct{
	float wheelRadius;
	float edgeRadius;
	float stripeLength;
	uint16_t numLeds;

	float period;
	float velocity;

	Stripes stripes;
}BikeInfo;

extern BikeInfo bikeInfo;

void bikeInfo_init();

#endif /* BIKEINFO_H_ */
