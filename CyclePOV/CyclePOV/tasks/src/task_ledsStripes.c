#include "task_ledsStripes.h"

#include "FreeRTOSIncludes.h"
#include "task_loader.h"
#include "processor.h"
#include "bikeInfo.h"
#include "defines.h"
#include "bsp_sensor.h"
#include "bsp_timer.h"
#include "bsp_ledsStripes.h"
#include "bsp_leds.h"
#include <stdint.h>

#define MAX_PERIOD_MS	1500
#define MAX_PERIOD		TIM_US_TO_TICKS(MAX_PERIOD_MS*1000)
#define MAX_ANGLE		2.0*M_PI*1.2

SemaphoreHandle_t txCompleteSemph;

uint32_t time[10];
volatile float usTime;

//Blocking send
void sendStripes();
//Turn off all LEDs of stripes. Blocking send
void turnOffStripes();
//Gets a frame, process it, and sends stripes
void displayAnimation();

void task_ledsStripes(void* args){
	//Wait for loader task initialization
	xSemaphoreTake(endLoaderInitSemph, portMAX_DELAY);

	txCompleteSemph = xSemaphoreCreateBinary();

	bikeInfo_init();	//Setup bike info first
	bsp_sensor_init();
	bsp_timer_init();
	bsp_ledsStripes_init();
	turnOffStripes();

	while(1){
		if(bikeInfo.period < MAX_PERIOD){
			bsp_leds_off();
			time[0] = bsp_timer_getTime();
			displayAnimation();
			time[7] = bsp_timer_getTime();
			time[8] = bsp_timer_getTime();
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
	time[1] = bsp_timer_getTime();

	//Reset angles
	previusAngle = -1.0;
	angle = 0.0;

	//Process and send all frame stripes
	while(angle > previusAngle){
		time[2] = bsp_timer_getTime();
		previusAngle = angle;
		angle = bsp_sensor_getAngle();

		//Checks if wheel is stopped
		if(angle > MAX_ANGLE){
			bikeInfo.period = UINT32_MAX;	//The period is infinite
			break;
		}
		else{
			time[3] = bsp_timer_getTime();
			process(angle, frame);
			time[4] = bsp_timer_getTime();
			sendStripes();
			time[5] = bsp_timer_getTime();
		}
		time[6] = bsp_timer_getTime();
	}
}

void sendStripes(){
	bsp_ledsStripes_sendStripes();
	time[9] = bsp_timer_getTime();
	//Wait for transmission complete
	xSemaphoreTake(txCompleteSemph, portMAX_DELAY);
}

void turnOffStripes(){
	bsp_ledsStripes_setOff();
	//Wait for transmission complete
	xSemaphoreTake(txCompleteSemph, portMAX_DELAY);
}

void bsp_ledsStripes_sendCompleteIRQ(){
	BaseType_t higherPriorityTaskWoken;
	//Indicate the end of transmission
	xSemaphoreGiveFromISR(txCompleteSemph, &higherPriorityTaskWoken);
	portYIELD_FROM_ISR(higherPriorityTaskWoken);
}
