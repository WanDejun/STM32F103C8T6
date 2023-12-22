#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "PWM.h"

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
	PWM_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Hello World!");
	
	uint16_t light;
	
	while (1) {
		for (light = 0; light <= 50; light++) {
			PWN_SetCompare1(light);
			Delay_ms(10);
		}
		for (light = 49; light > 0; light--) {
			PWN_SetCompare1(light);
			Delay_ms(10);
		}
	}
}
 
