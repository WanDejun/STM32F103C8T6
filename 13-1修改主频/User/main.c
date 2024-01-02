#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"

uint16_t Key_Num;


static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	OLED_Init();
}

int main(void) {
	Init();
	
	OLED_ShowNum(1, 1, SystemCoreClock, 8);
	
	while (1) {
		OLED_ShowString(2, 1, "Runing");
		Delay_ms(1000);
		OLED_ShowString(2, 1, "      ");
		Delay_ms(1000);
	}
}
 
