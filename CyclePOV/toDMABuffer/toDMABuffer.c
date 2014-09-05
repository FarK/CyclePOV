#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ONE	6
#define ZERO	4

uint32_t _toDMABuffer[256];
uint8_t toDMABuffer[256][3];

void initArrays();
void setBit(uint8_t byte, uint8_t bit);
void print();
const char *toBinary(uint8_t value);

int main(){
	initArrays();
	print();

	return 0;
}

void initArrays(){
	int word,bit;

	for(word=0 ; word<256 ; ++word){
		for(bit=0 ; bit<8 ; ++bit){
			setBit(word, bit);
		}
	}

	for(word=0 ; word<256 ; ++word){
		toDMABuffer[word][0] = (_toDMABuffer[word] & 0xFF0000) >> 8*2;
		toDMABuffer[word][1] = (_toDMABuffer[word] & 0x00FF00) >> 8*1;
		toDMABuffer[word][2] = (_toDMABuffer[word] & 0x0000FF) >> 8*0;
	}
}

void setBit(uint8_t byte, uint8_t bit){
	uint8_t value = (byte >> bit) & 1;
	uint8_t bitPos = bit*3;

	if(value){
		uint32_t mask = ONE << bitPos;
		_toDMABuffer[byte] |= mask;
	}else{
		uint32_t mask = ZERO << bitPos;
		_toDMABuffer[byte] |= mask;
	}
}

void print(){
	int byte;

	printf("#ifndef TO_DMA_BUFFER_ARRAY_H_\n");
	printf("#define TO_DMA_BUFFER_ARRAY_H_\n\n");
	printf("const uint8_t toDMABuffer[256][3] = {\n");

	for(byte=0 ; byte<255 ; ++byte){
		printf("\t{\n");
		printf("\t\t0x%02X,\t//0b%s\n", toDMABuffer[byte][0], toBinary(toDMABuffer[byte][0]));
		printf("\t\t0x%02X,\t//0b%s\n", toDMABuffer[byte][1], toBinary(toDMABuffer[byte][1]));
		printf("\t\t0x%02X\t//0b%s\n", toDMABuffer[byte][2], toBinary(toDMABuffer[byte][2]));
		printf("\t},\n");
	}
	printf("\t{\n");
	printf("\t\t0x%02X,\t//0b%s\n", toDMABuffer[byte][0], toBinary(toDMABuffer[byte][0]));
	printf("\t\t0x%02X,\t//0b%s\n", toDMABuffer[byte][1], toBinary(toDMABuffer[byte][1]));
	printf("\t\t0x%02X\t//0b%s\n", toDMABuffer[byte][2], toBinary(toDMABuffer[byte][2]));
	printf("\t}\n");

	printf("};\n\n");
	printf("#endif /* TO_DMA_BUFFER_ARRAY_H_ */\n");
}

const char *toBinary(uint8_t value) {
	static char b[9];
	b[0] = '\0';

	int z;
	for (z = 0x80; z > 0; z >>= 1)
		strcat(b, ((value & z) == z) ? "1" : "0");

	return b;
}
