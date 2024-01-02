#include "stm32f10x.h"                  // Device header
#include "Serial.h"

static uint8_t RxFlag;
uint8_t Serial_RxPacket[32];

void Serial_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitSturcture;
	USART_InitSturcture.USART_BaudRate = 115200;
	USART_InitSturcture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturcture.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitSturcture.USART_StopBits = USART_StopBits_1;
	USART_InitSturcture.USART_Parity = USART_Parity_No;
	USART_InitSturcture.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitSturcture);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t Byte) {
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendString(char *str) {
	while (*str != '\0') {
		Serial_SendByte((uint8_t)*str);
		str++;
	}
}

uint8_t Serial_GetRxFlag(void) {
	if (RxFlag == 1) {
		RxFlag = 0;
		return 1;
	}
	return 0;
}

void Serial_SendPacket(char *str) {
	Serial_SendString(str);
}

void USART1_IRQHandler(void) {
	static uint8_t loc = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		Serial_RxPacket[loc++] = USART_ReceiveData(USART1);
		if (Serial_RxPacket[loc - 1] == '\n') {
			Serial_RxPacket[loc - 1] = '\0';
			loc = 0;
			RxFlag = 1;
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
