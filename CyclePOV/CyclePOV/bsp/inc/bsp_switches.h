#ifndef BSP_SWITCHES_H_
#define BSP_SWITCHES_H_

#include <stdint.h>

typedef enum{
	FIRST_STRIPES,
	LAST_STRIPES,
	BOTH_STRIPES,
	INVALID
}SwitchesState;

extern const uint8_t swXToSwitchState[2][2];

void bsp_switches_init();
/* Read switches state and change stripes */
void bsp_switchesIRQ(uint8_t sw1, uint8_t sw2) __attribute__((weak));

#endif /* BSP_SWITCHES_H_ */
