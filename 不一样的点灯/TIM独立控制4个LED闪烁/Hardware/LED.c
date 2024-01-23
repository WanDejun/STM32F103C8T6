#include "LED.h"
#include "stm32f10x.h"                  // Device header

void LED_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, Bit_RESET);
}

void LED_ON(uint16_t GPIO_Pin) {
	GPIO_WriteBit(GPIOA, GPIO_Pin, Bit_SET);
}

void LED_OFF(uint16_t GPIO_Pin) {
	GPIO_WriteBit(GPIOA, GPIO_Pin, Bit_RESET);
}
void LED_Flip(uint16_t GPIO_Pin) {
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin)) {
		GPIO_WriteBit(GPIOA, GPIO_Pin, Bit_RESET);
	}
	else {
		GPIO_WriteBit(GPIOA, GPIO_Pin, Bit_SET);
	}
	
}
