#ifndef BSP_DMA_H_
#define BSP_DMA_H_

#include "bikeInfo.h"
#include <stdint.h>

#define SPI_BITS_PER_BIT		3
#define SPI_BYTE_PER_BYTE		SPI_BITS_PER_BIT
#define MAX_STRIPES_BUFF_SIZE	MAX_NUM_STRIPES*MAX_NUM_LEDS*sizeof(LED)*SPI_BYTE_PER_BYTE
#define MAX_BUFF_SIZE			MAX_STRIPES_BUFF_SIZE + sizeof(uint8_t) + sizeof(uint16_t)

typedef struct{
	union{
		struct{
			uint8_t head;
			uint8_t stripes[MAX_STRIPES_BUFF_SIZE];
			uint16_t tail;
		};
		uint8_t buffer[MAX_BUFF_SIZE];
	};
	unsigned int stripesBuffSize;
	unsigned int buffSize;
}DMABuffer;

void bsp_dma_init();
void bsp_dma_stripesToDMABuff();
void bsp_dma_clearBuffer();
void bsp_dma_enable();
void bsp_dma_disable();
void bsp_dma_TxCompleteIRQ() __attribute__((weak));

#endif /* BSP_DMA_H_ */
