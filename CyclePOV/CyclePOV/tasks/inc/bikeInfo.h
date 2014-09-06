#ifndef BIKEINFO_H_
#define BIKEINFO_H_

#include <stdint.h>

#define MAX_WHEEL_RADIUS	27.5	//Radius wheel in cm
#define MAX_EDGE_RADIUS		3.5		//Edge radius in cm
#define MAX_STRIPE_LENGTH	(MAX_WHEEL_RADIUS - MAX_EDGE_RADIUS)
#define MAX_NUM_LEDS		36		//Max number of LEDs in the stripe
#define MIN_NUM_LEDS		14		//Min number of LEDs in the stripe
#define MAX_NUM_STRIPES		8		//Max number of LEDs stripes
#define SENSOR_ANGLE		25.0/180.0*PI	//Angle between hall sensor and first stripe

typedef uint8_t LED[3];

typedef struct{
	LED leds[MAX_NUM_LEDS];
	uint8_t numLeds;
	float angle;	//Stripe angle in rad
	//Indexes to fix broken leds and displaced stripes
	uint8_t startLed;
	uint8_t endLed;
}Stripe;

typedef struct{
	Stripe stripes[MAX_NUM_STRIPES];
	uint8_t numStripes;
	uint16_t numLeds;
	//Pointers to swap stripes
	Stripe* starStripe;
	Stripe* endStripe;
}Stripes;

typedef struct{
	float wheelRadius;
	float edgeRadius;
	float stripeLength;

	uint32_t period;
	float velocity;
}BikeInfo;

extern BikeInfo bikeInfo;
extern Stripes stripes;

void bikeInfo_init();

#endif /* BIKEINFO_H_ */
