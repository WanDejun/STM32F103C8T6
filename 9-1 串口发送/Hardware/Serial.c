#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "stdio.h"
#include "stdarg.h"

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
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600; //波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t Byte) {
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t* Byte, uint16_t size) {
	int i;
	for (i = 0; i < size; i++) {
		Serial_SendByte(Byte[i]);
	}
}

void Serial_SendString(const char* str) {
	int i = 0;
	while (str[i] != '\0') {
		Serial_SendByte(str[i]);
		i++;
	}
}

static uint32_t pow(uint16_t a, uint16_t b) {
	if (b == 0) return 1;
	return b & 1 ? a * pow(a * a, b >> 1) : pow(a * a, b >> 1);
}

void Serial_SendNum(uint32_t Num, uint8_t Length) {
	int i;
	for (i = Length - 1; i >= 0; i--) {
		Serial_SendByte(Num / pow(10, i) % 10 + '0');
	}
}

void Serial_Printf(const char* Format, ...) {
	char str[100];
	va_list arg;
	va_start(arg, Format);
	vsprintf(str, Format, arg);
	va_end(arg);
	Serial_SendString(str);
}

//int fputc(int ch, FILE* f) {
//	Serial_SendByte(ch);
//	return ch;
//}
