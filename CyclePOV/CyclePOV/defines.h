#ifndef DEFINES_H_
#define DEFINES_H_

#include "portmacro.h"

#define DEBUG 1

#define MS_TO_TICKS(ms)	(ms/portTICK_PERIOD_MS)
#define TICKS_TO_MS(ticks) ((float)ticks*(float)portTICK_PERIOD_MS)

void assert_failed(uint8_t* file, uint32_t line);

#endif /* DEFINES_H_ */
