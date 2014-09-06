#include <stdint.h>

#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_

void bsp_timer_init();
uint32_t bsp_timer_getTime();
void bsp_timer_reset();
void bsp_timer_setCount(uint32_t count);
void bsp_timer_timeOutIRQ() __attribute__((weak));

#endif /* BSP_TIMER_H_ */
