#include "stm32f10x.h"                  // Device header
#include "MySPI.h"

static void MySPI_W_SS(uint8_t BitValue) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

static void MySPI_W_SCK(uint8_t BitValue) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}

static void MySPI_W_MOSI(uint8_t BitValue) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}

static uint8_t MySPI_R_MISO(void) {
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySPI_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	MySPI_W_SS(1);
	MySPI_W_SCK(0);
}

void MySPI_Start(void) {
	MySPI_W_SS(0);
}

void MySPI_Stop(void) {
	MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t Byte) {
	int8_t loc = 8;	
	
	while (loc) {
		MySPI_W_MOSI(Byte & 0x80);
		Byte <<= 1;
		MySPI_W_SCK(1); //全程不用延迟，W25Q64速度为80MHz
		Byte |= MySPI_R_MISO();
		MySPI_W_SCK(0);
		loc--;
	}
	
	return Byte;
}
