#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t AD_Value;

/*PA0 接滑动变阻器中间脚
PA2接光敏电阻AD端*/

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
	AD_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Volatge0:0.000V");
	OLED_ShowString(2, 1, "Volatge1:0.000V");
	OLED_ShowString(3, 1, "Volatge2:0.000V");
	
	while (1) {
		AD_Value = AD_GetValue(ADC_Channel_0) * 3.3 / 4095 * 1000;
		OLED_ShowNum(1, 10, AD_Value / 1000, 1);
		OLED_ShowNum(1, 12, AD_Value % 1000, 3);
		
		AD_Value = AD_GetValue(ADC_Channel_1) * 3.3 / 4095 * 1000;
		OLED_ShowNum(2, 10, AD_Value / 1000, 1);
		OLED_ShowNum(2, 12, AD_Value % 1000, 3);
		
		AD_Value = AD_GetValue(ADC_Channel_2) * 3.3 / 4095 * 1000;
		OLED_ShowNum(3, 10, AD_Value / 1000, 1);
		OLED_ShowNum(3, 12, AD_Value % 1000, 3);
		
		Delay_ms(50);
	}
}
 
