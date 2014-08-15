#include "bmp.h"

#include <stdio.h>

#if BIG_ENDIAN == 1
void* toLittleEndian(void* data, SIZE size) {
	BYTE* cdata = data;
	int i;
	for (i=0; i<size/2; i++) {
		BYTE temp = cdata[i];
		cdata[i] = cdata[size-1 - i];
		cdata[size-1 - i] = temp;
	}

	return data;
}
#endif

BMPError bmp_read(BMP_FILE* file, void* buff, SIZE count, SIZE* read){
	FRESULT error = f_read(file, buff, count, read);

	if(error)	return BMP_ERROR;
	else		return BMP_OK;
}

BMPError bmp_seek(BMP_FILE* file, SIZE offset){
	FRESULT error = f_lseek(file, offset);

	if(error)	return BMP_ERROR;
	else		return BMP_OK;
}
