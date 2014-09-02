#ifndef BSP_LEDSSTRIPES_H_
#define BSP_LEDSSTRIPES_H_

#include "bikeInfo.h"

#define BIT_TX_TIME_US		1.2
#define LED_TX_TIME_US		BIT_TX_TIME_US*((float)(sizeof(LED)*8*3))
#define RESET_TX_TIME_US	51.0

void bsp_ledsStripes_init();
void bsp_ledsStripes_sendStripes();
void bsp_ledsStripes_setOff();
void bsp_ledsStripes_sendCompleteIRQ() __attribute__ ((weak));

#endif /* BSP_LEDSSTRIPES_H_ */
