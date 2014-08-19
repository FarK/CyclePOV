#include "bmp.h"

#include "assert.h"

//AUX PRIVATE FUNCTIONS
BMPError bmp_check_FileHeader(BMP_FileHeader* fileHeader);
BMPError bmp_check_DIB(BMP_DIB* DIB);

/** Load and decode bmp file into BMP structure **/
BMPError bmp_load(BMP_FILE* file, BMP* bmp){
	BMPError error;

	//READ AND CHECK FILE HEADER
	error = bmp_load_fileHeader(file, &bmp->fileHeader);
	if(error)	return error;

	//READ AND CHECK DIB
	error = bmp_load_DIB(file, &bmp->DIB);
	if(error)	return error;

	bmp_setArrayInfo(&bmp->DIB, &bmp->arrayInfo);

	//LOAD IMAGE ARRAY
	error = bmp_load_pixels(file, bmp);
	if(error)	return error;

	return BMP_OK;
}

BMPError bmp_check_FileHeader(BMP_FileHeader* fileHeader){
	if(fileHeader->type != BMP_TYPE) return BMP_INVALID_FILE_HEADER;
	return BMP_OK;
}

//Filter supported BMP files
BMPError bmp_check_DIB(BMP_DIB* DIB){
	//Absolute size
	DWORD Width = DIB->width > 0? DIB->width : -DIB->width;
	DWORD Height = DIB->height > 0? DIB->height : -DIB->height;

	if(
	   DIB->DIBSize < DIB_SIZE		||
	   Width > BMP_MAX_WIDTH		||
	   Height > BMP_MAX_HEIGHT		||
	   DIB->imgSize > BMP_MAX_SIZE	||
	   DIB->bitsPerPixel != 24		||
	   DIB->compression != BMP_BI_RGB
	)
		return BMP_INVALID_DIB;

	return BMP_OK;
}

/** Load and decode file header into its structure **/
BMPError bmp_load_fileHeader(BMP_FILE* file, BMP_FileHeader* fileHeader){
	BYTE buff[FILE_HEADER_SIZE];
	SIZE read;
	BMPError error;

	if((error = (bmp_read(file, &buff[0], FILE_HEADER_SIZE, &read))) != BMP_OK)
		return error;

	getWordFromBuff(fileHeader->type, buff, 0);
	getDWordFromBuff(fileHeader->fileSize, buff, 2);
	getDWordFromBuff(fileHeader->reserved, buff, 6);
	getDWordFromBuff(fileHeader->offset, buff, 10);

	return bmp_check_FileHeader(fileHeader);
}

/** Load and decode DIB header into its structure **/
BMPError bmp_load_DIB(BMP_FILE* file, BMP_DIB* DIB){
	BYTE buff[DIB_SIZE];
	SIZE read;
	BMPError error;

	if((error = (bmp_read(file, &buff[0], DIB_SIZE, &read))) != BMP_OK)
		return error;

	getDWordFromBuff(DIB->DIBSize, buff, 0);
	getDWordSFromBuff(DIB->width, buff, 4);
	getDWordSFromBuff(DIB->height, buff, 8);
	getWordFromBuff(DIB->planes, buff, 12);
	getWordFromBuff(DIB->bitsPerPixel, buff, 14);
	getDWordFromBuff(DIB->compression, buff, 16);
	getDWordFromBuff(DIB->imgSize, buff, 20);
	getDWordFromBuff(DIB->horizontalRes, buff, 24);
	getDWordFromBuff(DIB->verticalRes, buff, 28);
	getDWordFromBuff(DIB->paletteColors, buff, 32);
	getDWordFromBuff(DIB->importantColors, buff, 36);

	return bmp_check_DIB(DIB);
}

void bmp_setArrayInfo(BMP_DIB* DIB, BMP_ArrayInfo* arrayInfo){
	arrayInfo->Width = (DIB->width > 0)? DIB->width : -DIB->width;
	arrayInfo->Height = (DIB->height > 0)? DIB->height : -DIB->height;

	arrayInfo->bytesPerPixel = DIB->bitsPerPixel/8;

	arrayInfo->padding = (arrayInfo->Width*arrayInfo->bytesPerPixel)%4;
	if(arrayInfo->padding) arrayInfo->padding = 4 - arrayInfo->padding;

	arrayInfo->rowBytes = arrayInfo->bytesPerPixel*(arrayInfo->Width) + arrayInfo->padding;
}

/** Load bmp pixel array. The headers need to be loaded first **/
BMPError bmp_load_pixels(BMP_FILE* file, BMP* bmp){
	SIZE read;

	//Desplace file pointer to pixel array
	if(bmp_seek(file, bmp->fileHeader.offset))
		return BMP_READ_ERROR;

	//LOAD PIXELS ARRAY TO MEM
	ASSERT(BMP_MAX_SIZE >= bmp->DIB.imgSize);
	if(bmp_read(file, &bmp->pixels, bmp->DIB.imgSize, &read))
		return BMP_READ_ERROR;
	ASSERT(read == bmp->DIB.imgSize);

	return BMP_OK;
}

BYTE* bmp_getPixel(SIZE x, SIZE y, BMP* bmp){
	//TODO: Implementar tamaños negativos
	SIZE delta = x*bmp->arrayInfo.bytesPerPixel + bmp->arrayInfo.rowBytes*y;
	return ((BYTE*)&bmp->pixels[0]) + delta;
}
