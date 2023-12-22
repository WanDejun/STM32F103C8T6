#include "stm32f10x.h"

void LED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
}

void LED_set(uint16_t Pin, BitAction Action) { // BitSet or BitReset
		GPIO_WriteBit(GPIOA, Pin, Action);
}

void LED_Flip(uint16_t Pin) {
	if (GPIO_ReadOutputDataBit(GPIOA, Pin) == 1) 
		LED_set(Pin, Bit_RESET);
	else
		LED_set(Pin, Bit_SET);
}
