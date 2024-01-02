#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "PWM.h"
#include "Key.h"

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
	PWM_Init();
	Key_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Hello World!");
	
	uint16_t light;
	
	PWN_SetCompare1(50);
	
	uint8_t num = 0;
	
	while (1) {
		if (Key_GetNum()) { 
			num = (num + 20) % 200;
			PWN_SetCompare1(num + 50); 
		}
	}
}
 
