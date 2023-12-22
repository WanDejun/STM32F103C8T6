#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t AD_Value;

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
	AD_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Volatge:0.000V");
	
	while (1) {
		AD_Value = AD_GetValue() * 3.3 / 4095 * 1000;
		OLED_ShowNum(1, 9, AD_Value / 1000, 1);
		OLED_ShowNum(1, 11, AD_Value % 1000, 3);
		Delay_ms(50);
	}
}
 
