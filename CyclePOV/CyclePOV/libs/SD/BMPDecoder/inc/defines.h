#ifndef BMP_PORT_H_
#define BMP_PORT_H

#include <stdio.h>
#include <stdint.h>
#include "ff.h"

#define DEBUG_LOG	0

#define BMP_MAX_WIDTH	128
#define BMP_MAX_HEIGHT	128
#define BMP_MAX_DEEP	3
#define BMP_MAX_SIZE	BMP_MAX_WIDTH*BMP_MAX_HEIGHT*BMP_MAX_DEEP

#define SIZE	UINT
#define BYTE	uint8_t
#define WORD	uint16_t
#define DWORD	uint32_t
#define LWORD	uint64_t
#define DWORD_S	int32_t

#define BMP_FILE FIL

#define getFromBuff(dest, buff, offset, type) dest = *((type*)&buff[offset])
#define getByteFromBuff(dest, buff, offset) getFromBuff(dest, buff, offset, BYTE)
#define getWordFromBuff(dest, buff, offset) getFromBuff(dest, buff, offset, WORD)
#define getDWordFromBuff(dest, buff, offset) getFromBuff(dest, buff, offset, DWORD)
#define getDWordSFromBuff(dest, buff, offset) getFromBuff(dest, buff, offset, DWORD_S)

#endif /* BMP_PORT_H */
