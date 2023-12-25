#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "MySPI.h"
#include "Delay.h"
#include "LED.h"

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	MySPI_Init();
	LED_Init();
}

int main(void) {
	Init();
	
	while (1) {
		OLED_ShowString(1, 1, (char*)Data);
	}
}
 
