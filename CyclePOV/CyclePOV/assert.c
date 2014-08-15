#include "assert.h"

#include "stm32f4_discovery.h"

#ifdef DEBUG
void assert_failed(uint8_t* file, uint32_t line){
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);

	while(1){
		STM_EVAL_LEDToggle(LED3);
		STM_EVAL_LEDToggle(LED4);
		STM_EVAL_LEDToggle(LED5);
		STM_EVAL_LEDToggle(LED6);

		int i = 1e7;
		while(i--);
	}
}
#endif
