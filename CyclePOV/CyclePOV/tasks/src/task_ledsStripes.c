#include "task_ledsStripes.h"

#include "FreeRTOSIncludes.h"
#include "task_loader.h"
#include "processor.h"
#include "bikeInfo.h"
#include "defines.h"
#include "bsp_sensor.h"
#include "bsp_ledsStripes.h"
#include "bsp_leds.h"
#include "bsp_switches.h"
#include "bsp_userButton.h"
#include <stdint.h>

#define MAX_PERIOD_MS	1500
#define MAX_PERIOD		TIM_US_TO_TICKS(MAX_PERIOD_MS*1000)
#define MAX_ANGLE		2.0*M_PI*1.2

DisplayState displayState = ANIMATION;

SemaphoreHandle_t txCompleteSemph;

//Blocking send
void sendStripes();
//Turn off all LEDs of stripes. Blocking send
void turnOffStripes();
//Turn on (white) all LEDs of stripes. Blocking send
void turnOnStripes();
//Gets a frame, process it, and sends stripes
void displayAnimation();
//Angular resolution test
void displayAngularResTest();

void task_ledsStripes(void* args){
	//Wait for loader task initialization
	xSemaphoreTake(endLoaderInitSemph, portMAX_DELAY);

	txCompleteSemph = xSemaphoreCreateBinary();

	bikeInfo_init();	//Setup bike info first
	bsp_switches_init();
	bsp_userButton_init();
	bsp_sensor_init();
	//bsp_timer_init();
	bsp_ledsStripes_init();
	turnOffStripes();

	while(1){
		if(bikeInfo.period < MAX_PERIOD){
			bsp_leds_off();

			switch(displayState){
				case ANIMATION:
					displayAnimation();
				break;

				case ANGULAR_RES_TEST:
					displayAngularResTest();
				break;
			}
		}
		else{
			turnOffStripes();
			bsp_leds_round();
			vTaskDelay(MS_TO_TICKS(100));
		}
	}
}

void displayAnimation(){
	static BMP* frame;
	static BMP* previousFrame = NULL;
	static float angle;
	static float previusAngle;

	//Wait for next frame
	frame = getNextFrame();
	if(previousFrame != frame){
		processConfig(frame);
		previousFrame = frame;
	}

	//Reset angles
	previusAngle = -1.0;
	angle = 0.0;

	//Process and send all frame stripes
	while(angle > previusAngle){
		previusAngle = angle;
		angle = bsp_sensor_getAngle();

		//Checks if wheel is stopped
		if(angle > MAX_ANGLE){
			bikeInfo.period = UINT32_MAX;	//The period is infinite
			break;
		}
		else{
			process(angle, frame);
			sendStripes();
		}
	}
}

void displayAngularResTest(){
	static float angle;

	turnOnStripes();
	turnOffStripes();

	angle = bsp_sensor_getAngle();
	if(angle > MAX_ANGLE){
		bikeInfo.period = UINT32_MAX;	//The period is infinite
	}
}

void sendStripes(){
	bsp_ledsStripes_sendStripes();
	//Wait for transmission complete
	xSemaphoreTake(txCompleteSemph, portMAX_DELAY);
}

void turnOffStripes(){
	bsp_ledsStripes_setOff();
	//Wait for transmission complete
	xSemaphoreTake(txCompleteSemph, portMAX_DELAY);
}

void turnOnStripes(){
	bsp_ledsStripes_setOn();
	//Wait for transmission complete
	xSemaphoreTake(txCompleteSemph, portMAX_DELAY);
}

void bsp_ledsStripes_sendCompleteIRQ(){
	BaseType_t higherPriorityTaskWoken;
	//Indicate the end of transmission
	xSemaphoreGiveFromISR(txCompleteSemph, &higherPriorityTaskWoken);
	portYIELD_FROM_ISR(higherPriorityTaskWoken);
}

void bsp_switchesIRQ(uint8_t sw1, uint8_t sw2){
	SwitchesState switchesState = swXToSwitchState[sw1][sw2];

	switch(switchesState){
		case FIRST_STRIPES:
			stripes.starStripe = &stripes.stripes[0];
			stripes.endStripe  = &stripes.stripes[3];
		break;

		case LAST_STRIPES:
			stripes.starStripe = &stripes.stripes[4];
			stripes.endStripe  = &stripes.stripes[7];
		break;

		case BOTH_STRIPES:
			stripes.starStripe = &stripes.stripes[0];
			stripes.endStripe  = &stripes.stripes[7];
		break;

		case INVALID:
			stripes.starStripe = &stripes.stripes[4];
			stripes.endStripe  = &stripes.stripes[7];
		break;
	}
}

void bsp_userButtonIRQ(){
	displayState = !displayState;
}
