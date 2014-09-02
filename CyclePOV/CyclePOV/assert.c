#include "assert.h"

#include "bsp_leds.h"

#ifdef DEBUG
void assert_failed(uint8_t* file, uint32_t line){
	bsp_leds_init();
	bsp_leds_off();

	while(1){
		bsp_leds_toggle();

		//Delay
		int i = 1e7;
		while(i--);
	}
}
#endif
