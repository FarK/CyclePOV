#include "bmp.h"

#include <stdio.h>

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
