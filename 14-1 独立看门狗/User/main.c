#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	OLED_Init();
	Key_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Start");
	
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST)) {
		OLED_ShowString(2, 1, "IWDGReset");
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
	
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499);
	IWDG_ReloadCounter();
	IWDG_Enable();
	
	while (1) {
		Key_GetNum();
		
		OLED_ShowString(4, 1, "Running");
		Delay_ms(400);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(400);
		IWDG_ReloadCounter();
	}
}
 
