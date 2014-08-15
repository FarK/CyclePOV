#include "bsp_loader.h"
#include "ff.h"

#include "stm32f4_discovery.h"

void bsp_loader_init(){
	STM_EVAL_LEDInit(LED3);
}
