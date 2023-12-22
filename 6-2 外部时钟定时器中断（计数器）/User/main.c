#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t num;


static void Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Timer_Init();
	OLED_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Num:");
	OLED_ShowString(2, 1, "Cnt:");
	
	while (1) {
		OLED_ShowNum(1, 5, num, 5);
		OLED_ShowNum(2, 5, Timer_GetCounter(), 5);
	}
}
 
