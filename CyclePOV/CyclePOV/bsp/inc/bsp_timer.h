#include <stdint.h>

#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_

#define TIMER_FREQ 160 //MHz
#define TIM_TICKS_TO_US(ticks) (ticks/TIMER_FREQ)
#define TIM_US_TO_TICKS(us) (us*TIMER_FREQ)

void bsp_timer_init();
uint32_t bsp_timer_getTime();
void bsp_timer_reset();
void bsp_timer_setCount(uint32_t count);
void bsp_timer_timeOutIRQ() __attribute__((weak));

#endif /* BSP_TIMER_H_ */
