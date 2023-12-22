#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint16_t num;


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
	PWM_SetCompare1(50);
	PWM_SetPrescaler(360 - 1);
	
	while (1) {
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);
	}
}
 
