#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	OLED_Init();
	Key_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Start");
	
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST)) {
		OLED_ShowString(2, 1, "WWDGReset");
		RCC_ClearFlag();
	}
	else  {
		OLED_ShowString(2, 1, "          ");
	}
	
	if (RCC_GetFlagStatus(RCC_FLAG_PINRST)) {
		OLED_ShowString(3, 1,"KeyReset");
		RCC_ClearFlag();
	}
	else {
		OLED_ShowString(3, 1,"        ");
	}
	
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0x40 | 21);
	WWDG_Enable(0x40 | 55);
	
	while (1) {
		Key_GetNum();
		
		OLED_ShowString(4, 1, "Running");
		Delay_ms(20);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(20);
		WWDG_SetCounter(0x40 | 55); 
	}
}
 
