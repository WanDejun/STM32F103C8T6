#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"

uint16_t Key_Num;

static void Init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断分组
	
	OLED_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Hello World!");
	
	while (1) {
		;
	}
}
