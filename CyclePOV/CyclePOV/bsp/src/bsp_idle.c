#include "bsp_idle.h"

#include "stm32f4_discovery.h"

void bsp_idle_init(){
	STM_EVAL_LEDInit(LED7);
}
