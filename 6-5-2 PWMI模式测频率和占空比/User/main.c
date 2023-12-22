#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint16_t num;

/*
PA0(TIM2时钟输入)接PA6(TIM3 PWM波形输出)
*/

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
	PWM_Init();
	IC_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Freq:00000Hz");
	OLED_ShowString(2, 1, "Duty:00%");
	PWM_SetCompare1(30);
	PWM_SetPrescaler(720 - 1);
	
	while (1) {
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);
		OLED_ShowNum(2, 6, IC_GetDuty(), 2);
	}
}
 
