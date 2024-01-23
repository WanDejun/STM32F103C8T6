#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "TIM1.h"
#include "TIM2.h"
#include "TIM3.h"
#include "TIM4.h"

void Init(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	TIM1_Init();
	TIM2_Init();
	TIM3_Init();
	TIM4_Init();
}

int main(void) {
	Init();
	
	TIM1_SetTime(4000);
	TIM2_SetTime(3000);
	TIM3_SetTime(2000);
	TIM4_SetTime(1000);
	
	while (1);
	
	return 0;
}
