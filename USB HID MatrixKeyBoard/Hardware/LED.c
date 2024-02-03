#include "stm32f10x.h"

void LED_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_2);
}

void LED_Set(uint16_t Pin) { 
	GPIO_ResetBits(GPIOB, Pin);
}

void LED_Reset(uint16_t Pin) { 
	GPIO_SetBits(GPIOB, Pin);
}

void LED_Flip(uint16_t Pin) {
	GPIO_WriteBit(GPIOB, Pin, !GPIO_ReadOutputDataBit(GPIOB, Pin));
}
