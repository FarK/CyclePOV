#ifndef DEFINES_H_
#define DEFINES_H_

#include "portmacro.h"
#include <stdint.h>

#define DEBUG 1

#define MS_TO_TICKS(ms)	(ms/portTICK_PERIOD_MS)
#define TICKS_TO_MS(ticks) ((float)ticks*(float)portTICK_PERIOD_MS)


#define INDEX_FILE	"index.txt"	//Index path for animation
#define MAX_PATH_LENGTH 50
#define MAX_FRAMES 20

void assert_failed(uint8_t* file, uint32_t line);

#endif /* DEFINES_H_ */
