#include "stm32f10x.h"                  // Device header
#include "MySPI.h"

static void MySPI_W_SS(uint8_t BitValue) {
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)BitValue);
}

void MySPI_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	SPI_InitTypeDef SPI_InitSturcture;
	SPI_InitSturcture.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitSturcture.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitSturcture.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitSturcture.SPI_CRCPolynomial = 7;
	SPI_InitSturcture.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitSturcture.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线全双工
	SPI_InitSturcture.SPI_FirstBit = SPI_FirstBit_MSB; //高位先行
	SPI_InitSturcture.SPI_Mode = SPI_Mode_Master;
	SPI_InitSturcture.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI2, &SPI_InitSturcture);
	
	SPI_Cmd(SPI2, ENABLE);
	
	MySPI_W_SS(1);
}

void MySPI_Start(void) {
	MySPI_W_SS(0);
}

void MySPI_Stop(void) {
	MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t Byte) {
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET);
	SPI_I2S_SendData(SPI2, Byte);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) != SET);
	Byte = SPI_I2S_ReceiveData(SPI2);
	
	return Byte;
}

void MySPI_SwapArray(uint8_t* Array, uint8_t ArraySize) {
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET); //等待发送队列为空
	SPI_I2S_SendData(SPI2, *Array); //发送第0位
	Array++; //指针自增
	ArraySize--; //计数器自减
	while (ArraySize) {
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET); //等待发送队列为空
		SPI_I2S_SendData(SPI2, *Array); //发送下一位
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) != SET); //等待上一位传输完成
		*(Array - 1) = SPI_I2S_ReceiveData(SPI2); //接收上一位
		Array++;
		ArraySize--;
	}
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) != SET); 
	*(Array - 1) = SPI_I2S_ReceiveData(SPI2); //接收最后一位
}
