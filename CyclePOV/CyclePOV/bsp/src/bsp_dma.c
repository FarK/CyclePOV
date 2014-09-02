#include "bsp_dma.h"

#include "stm32f4xx.h"

DMABuffer dmaBuffer;

//AUX PRIVATE FUNCTIONS
void setBit(uint16_t bit, uint8_t value, uint8_t* dest);

void bsp_dma_init(){
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVICInit;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	// INTERRUPT CONFIG
	NVICInit.NVIC_IRQChannel = DMA1_Stream4_IRQn;
	NVICInit.NVIC_IRQChannelPreemptionPriority = 0x8;
	NVICInit.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVICInit);

	// DMA CONFIG
	DMA_DeInit(DMA1_Stream4);

	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (&(SPI2->DR));
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) dmaBuffer.buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;

	DMA_Init(DMA1_Stream4, &DMA_InitStructure);

	//Set buffer sizes
	dmaBuffer.stripesBuffSize = bikeInfo.numLeds*sizeof(LED)*SPI_BYTE_PER_BYTE;
	dmaBuffer.buffSize = dmaBuffer.stripesBuffSize + sizeof(uint8_t) + sizeof(uint16_t);

	bsp_dma_clearBuffer();
}

void DMA1_Stream4_IRQHandler(){
	bsp_dma_TxCompleteIRQ();
}

void setBit(uint16_t bit, uint8_t value, uint8_t* dest){
	uint16_t num_bit = bit * SPI_BITS_PER_BIT;

	uint16_t num_byte = (num_bit >> 3);
	// 0 is codified as 100 and 1 as 110
	// Only the central bit is changed
	uint8_t mask = 1 << (7 - ((num_bit) & 7));

	dest[num_byte] ^= (-value ^ dest[num_byte]) & mask;
	/* Same as:
	 * if(value == 1) (*dest)[num_byte] |= mask;
	 * else           (*dest)[num_byte] &= ~mask;
	 */
}

void bsp_dma_clearBuffer(){
	unsigned int i;

	dmaBuffer.head = 1; //First bit

	// 0 is codified as 100 and 1 as 110
	// Only the central bit is changed
	// 0x92 = 0b 100 100 10
	// 0x49 = 0b 0 100 100 1
	// 0x24 = 0b 00 100 100
	for (i = 0; i < dmaBuffer.stripesBuffSize; i+=3) {
		dmaBuffer.stripes[i + 0] = 0x24;
		dmaBuffer.stripes[i + 1] = 0x92;
		dmaBuffer.stripes[i + 2] = 0x49;
	}

	dmaBuffer.tail = 0;
}

void bsp_dma_stripesToDMABuff(){
	uint32_t num_bit = 0;
	unsigned int s,l,color,bit;
	uint8_t byte;
	Stripes* stripes = &bikeInfo.stripes;
	Stripe* stripe;

	for(s=0, stripe=&stripes->stripes[0];
		s<stripes->numStripes;
		++s, ++stripe)
	{
		for(l=0 ; l<stripe->numLeds ; ++l){
			for(color=0 ; color<3 ; ++color){
				byte = stripe->leds[l][color];
				for(bit=0 ; bit<8 ; ++bit){
					setBit(num_bit++, (byte >> (7 - bit)) & 1, &dmaBuffer.stripes[0]);
				}
			}
		}
	}
}

void bsp_dma_enable(){
	DMA_SetCurrDataCounter(DMA1_Stream4, dmaBuffer.buffSize);
	DMA_ITConfig(DMA1_Stream4, DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA1_Stream4, ENABLE);
}

void bsp_dma_disable(){
	DMA_Cmd(DMA1_Stream4, DISABLE);
	DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_TCIF4);
}
