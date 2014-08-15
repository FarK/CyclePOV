#ifndef ASSERT_H_
#define ASSERT_H_

#include "portmacro.h"
#include "defines.h"

#ifdef DEBUG
	#define USE_FULL_ASSERT 1

	void assert_failed(uint8_t* file, uint32_t line);

	#define ASSERT(x) if((x) == 0){ portDISABLE_INTERRUPTS(); assert_failed(0,0); }
#else
	#define ASSERT(x)
#endif
#define CHECK_ERROR(x)	ASSERT(!(x))

#endif /* ASSERT_H_ */
