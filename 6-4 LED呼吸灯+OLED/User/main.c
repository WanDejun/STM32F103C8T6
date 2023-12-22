#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "PWM.h"
#include "Timer.h"

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	PWM_Init();
	Timer_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(2, 7, "Time");
	OLED_ShowChar(3, 9, ':');
	
	uint16_t light;
	uint16_t time;
	
	while (1) {
		for (light = 0; light <= 50; light++) {
			PWN_SetCompare1(light);
			time = TimerGetCnt();
			OLED_ShowNum(3, 4, time, 5);
			OLED_ShowNum(3, 10, TIM_GetCounter(TIM3), 4);
			Delay_ms(19);
		}
		for (light = 49; light > 0; light--) {
			PWN_SetCompare1(light);
			time = TimerGetCnt();
			OLED_ShowNum(3, 4, time, 5);
			OLED_ShowNum(3, 10, TIM_GetCounter(TIM3), 4);
			Delay_ms(19);
		}
	}
}
 
