#ifndef BMP_H_
#define BMP_H_

#include "defines.h"

#define BMP_TYPE	0x4D42
#define BMP_BI_RGB	0x0

typedef enum{
	BMP_OK = 0,
	BMP_INVALID_FILE_HEADER,
	BMP_INVALID_DIB,
	BMP_READ_ERROR,
	BMP_ERROR
}BMPError;

//BMP HEADER
#define FILE_HEADER_SIZE 3*sizeof(DWORD) + sizeof(WORD)
typedef struct{
	WORD	type;
	DWORD	fileSize;
	DWORD	reserved;
	DWORD	offset;
}BMP_FileHeader;

#define DIB_SIZE 7*sizeof(DWORD) + 2*sizeof(WORD) + 2*sizeof(DWORD_S)
typedef struct{
	DWORD	DIBSize;
	DWORD_S	width;
	DWORD_S	height;
	WORD	planes;
	WORD	bitsPerPixel;
	DWORD	compression;
	DWORD	imgSize;
	DWORD	horizontalRes;
	DWORD	verticalRes;
	DWORD	paletteColors;
	DWORD	importantColors;
}BMP_DIB;

//BMP ARRAY
typedef BYTE Pixels[BMP_MAX_WIDTH][BMP_MAX_HEIGHT][BMP_MAX_DEEP];

typedef struct{
	DWORD	Width;
	DWORD	Height;
	BYTE	bytesPerPixel;
	DWORD	rowBytes;
	BYTE padding;
} BMP_ArrayInfo;

typedef struct{
	BMP_FileHeader fileHeader;
	BMP_DIB DIB;
	BMP_ArrayInfo arrayInfo;
	Pixels pixels;
}BMP;

//BMP FUNCTION
BMPError bmp_load_fileHeader(BMP_FILE* file, BMP_FileHeader* fileHeader);
BMPError bmp_load_DIB(BMP_FILE* file, BMP_DIB* DIB);
void     bmp_setArrayInfo(BMP_DIB* DIB, BMP_ArrayInfo* arrayInfo);
BMPError bmp_load_pixels(BMP_FILE* file, BMP* bmp);
BMPError bmp_load(BMP_FILE* file, BMP* bmp);
BYTE*    bmp_getPixel(SIZE x, SIZE y, BMP* bmp);

//PORTABLE FUNCTIONS FOR FILE READ
BMPError bmp_read(BMP_FILE* file, void* buff, SIZE count, SIZE* read);
BMPError bmp_seek(BMP_FILE* file, SIZE offset);

#endif /* BMP_H_ */
