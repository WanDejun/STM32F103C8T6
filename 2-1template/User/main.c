#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"

int main(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_5);
	
	while (1) {
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		Delay_ms(1000);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		Delay_ms(1000);
	}
}
 
