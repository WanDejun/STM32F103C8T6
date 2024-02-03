#include "74HC595.h"
#include "stm32f10x.h"                  // Device header

#define HC595BITCNT	8

#define DS_Pin		GPIO_Pin_0
#define RCK_Pin		GPIO_Pin_1
#define SCK_Pin		GPIO_Pin_10

#define DS_HIGH		GPIO_SetBits(GPIOB, DS_Pin)
#define DS_LOW		GPIO_ResetBits(GPIOB, DS_Pin)

#define RCK_HIGH	GPIO_SetBits(GPIOB, RCK_Pin)
#define RCK_LOW		GPIO_ResetBits(GPIOB, RCK_Pin)

#define SCK_HIGH	GPIO_SetBits(GPIOB, SCK_Pin)
#define SCK_LOW		GPIO_ResetBits(GPIOB, SCK_Pin)

static void delay(void) {
	__IO uint8_t i;
	for (i = 0; i < 128; i++) {
		;
	}
}

void _74HC595_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = DS_Pin | RCK_Pin | SCK_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	DS_LOW;
	SCK_LOW;
	RCK_LOW;
	
	uint8_t i, j;
	
	for (i = 0; i < HC595BITCNT; i++) {
		delay();
		SCK_HIGH;
		delay();
		SCK_LOW;
	}
	
	delay();
	RCK_HIGH;
	delay();
	RCK_LOW;
}

void _74HC595_Write(uint8_t Byte) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		if (Byte & 0x80) DS_HIGH;
		else DS_LOW;
		
		delay();
		SCK_HIGH;
		delay();
		SCK_LOW;
		
		Byte <<= 1;
	}
	
	DS_LOW; 		// DS复位
	
	RCK_HIGH;
	delay();
	RCK_LOW;
}

