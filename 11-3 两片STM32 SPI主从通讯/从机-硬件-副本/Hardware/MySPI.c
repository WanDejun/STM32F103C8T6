#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "LED.h"

uint8_t Cnt_Send, Cnt_Receive, Cnt_Max;
uint8_t Data[13] = { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x00 };

void MySPI_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
//	
//	EXTI_InitTypeDef EXTI_InitStructure;
//	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
//	EXTI_Init(&EXTI_InitStructure);
	
	SPI_InitTypeDef SPI_InitSturcture;
	SPI_InitSturcture.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitSturcture.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitSturcture.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitSturcture.SPI_CRCPolynomial = 7;
	SPI_InitSturcture.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitSturcture.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线全双工
	SPI_InitSturcture.SPI_FirstBit = SPI_FirstBit_MSB; //高位先行
	SPI_InitSturcture.SPI_Mode = SPI_Mode_Slave;
	SPI_InitSturcture.SPI_NSS = SPI_NSS_Hard;
	SPI_Init(SPI1, &SPI_InitSturcture);
	
//	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
//	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, ENABLE);
//	
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&NVIC_InitStructure);	
//		
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
//	NVIC_Init(&NVIC_InitStructure);	

	
	SPI_Cmd(SPI1, ENABLE);
	Cnt_Send = Cnt_Receive = Cnt_Max = 0;
}

uint8_t MySPI_SwapByte(uint8_t Byte) {
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	SPI_I2S_SendData(SPI1, Byte);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);
	Byte = SPI_I2S_ReceiveData(SPI1);	
	
	return Byte;
}

void MySPI_SwapArray(uint8_t* Array, uint8_t ArraySize) {
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET); //等待发送队列为空
	SPI_I2S_SendData(SPI1, *Array); //发送第0位
	Array++; //指针自增
	ArraySize--; //计数器自减
	while (ArraySize) {
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET); //等待发送队列为空
		SPI_I2S_SendData(SPI1, *Array); //发送下一位
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET); //等待上一位传输完成
		*(Array - 1) = SPI_I2S_ReceiveData(SPI1); //接收上一位
		Array++;
		ArraySize--;
	}
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET); 
	*(Array - 1) = SPI_I2S_ReceiveData(SPI1); //接收最后一位
}
