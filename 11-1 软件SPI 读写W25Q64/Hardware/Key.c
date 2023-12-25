#include "stm32f10x.h"                  // Device header
#include "delay.h"

void Key_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //引脚定义
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void) {
	uint8_t KeyNum = 0;

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0) {
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0);
		Delay_ms(20);
		KeyNum = 2;
	}
	
	return KeyNum;
}
