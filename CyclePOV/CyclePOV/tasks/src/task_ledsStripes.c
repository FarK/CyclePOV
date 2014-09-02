#include "task_ledsStripes.h"

#include "FreeRTOSIncludes.h"
#include "task_loader.h"
#include "processor.h"
#include "bikeInfo.h"
#include "defines.h"
#include "bsp_timer.h"
#include "bsp_ledsStripes.h"
#include "bsp_leds.h"
#include <tgmath.h>
#include <float.h>

#define MIN_PERIOD	10e3
#define MAX_ANGLE	2.0*M_PI*1.2

SemaphoreHandle_t txCompleteSemph;

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
	bsp_timer_init();
	bsp_ledsStripes_init();
	turnOffStripes();

	while(1){
		if(bikeInfo.period < MIN_PERIOD){
			bsp_leds_off();
			displayAnimation();
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
		angle = bsp_timer_getAngle();

		//Checks if wheel is stopped
		if(angle > MAX_ANGLE){
			bikeInfo.period = FLT_MAX;	//The period is infinite
			break;
		}
		else{
			process(angle, frame);
			sendStripes();
		}
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

void bsp_ledsStripes_sendCompleteIRQ(){
	BaseType_t higherPriorityTaskWoken;
	//Indicate the end of transmission
	xSemaphoreGiveFromISR(txCompleteSemph, &higherPriorityTaskWoken);
	portYIELD_FROM_ISR(higherPriorityTaskWoken);
}
