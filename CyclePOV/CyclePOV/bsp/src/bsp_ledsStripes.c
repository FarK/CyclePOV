#include "bsp_ledsStripes.h"

#include "bsp_dma.h"
#include "bsp_spi.h"

void bsp_ledsStripes_init(){
	bsp_dma_init();
	bsp_spi_init();
}

void bsp_ledsStripes_sendStripes(){
	bsp_dma_stripesToDMABuff();
	bsp_dma_enable();
}

void bsp_dma_TxCompleteIRQ(){
	bsp_dma_disable();
	bsp_ledsStripes_sendCompleteIRQ();
}

void bsp_ledsStripes_setOff(){
	bsp_dma_clearBuffer();
	bsp_dma_enable();
}

void bsp_ledsStripes_setOn(){
	bsp_dma_setBuffer();
	bsp_dma_enable();
}
