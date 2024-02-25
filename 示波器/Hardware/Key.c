#include "stm32f10x.h"                  // Device header
#include "Key.h"

#define KeyNum	2

#define KeyPin1	GPIO_Pin_12
#define KeyPin2	GPIO_Pin_13

static uint16_t KeyPin[KeyNum] = {KeyPin1, KeyPin2};

static uint8_t KeyBuffer1[(KeyNum + 7) >> 3], KeyBuffer2[(KeyNum + 7) >> 3];
uint8_t KeyState[(KeyNum + 7) >> 3];

void Key_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	uint8_t i;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = 0;
	for (i = 0; i < KeyNum; i++) {
		GPIO_InitStructure.GPIO_Pin |= KeyPin[i];
	}
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_Scan(void) {
	uint16_t data = GPIO_ReadInputData(GPIOB), mask;
	uint8_t i;
	for (i = 0; i < KeyNum; i++) {
		if ((~data & KeyPin[i])) KeyBuffer2[i >> 3] |= 1 << (i & 0x07);
		else KeyBuffer2[i >> 3] &= ~(1 << (i & 0x07));
	}
	data = 0;
	for (i = 0; i < (KeyNum + 7) >> 3; i++) {
		mask = ~(KeyBuffer1[i] ^ KeyBuffer2[i]);
		data |= (mask & KeyBuffer1[i]) ^ (mask & KeyState[i]);
		KeyState[i] = (KeyBuffer1[i] & mask) | (KeyState[i] & ~mask);
		KeyBuffer1[i] = KeyBuffer2[i];
	}
	return data;
}
