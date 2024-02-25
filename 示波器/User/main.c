#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "Key.h"
#include "TIM4.h"

void Init(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	AD_Init();
	Key_Init();
	TIM4_Init();
}

int main(void) {
	Init();
	uint8_t i;
	uint16_t Freq = 1000, MinVol, MaxVol;
	
	OLED_ShowString(32, 54, "ms", 6);
	OLED_ShowString(48, 54, "M:", 6); // 58-76
	OLED_ShowString(64, 54, ".", 6);
	OLED_ShowString(76, 54, "V", 6);
	OLED_ShowString(84, 54, "m:", 6); // 94-112
	OLED_ShowString(100, 54, ".", 6);
	OLED_ShowString(112, 54, "V", 6);
	
	AD_SetIntervalTime(Freq);
	AD_TimingTriggerStart();
	OLED_ShowNum(0, 48, Freq, 4, 8);
	
	OLED_Update();
	
	while (1) {
		if (AD_GetFinishFlag()) {
			OLED_DrawBKNet();
			MaxVol = 0;
			MinVol = 0xfff;
			for (i = 0; i < 128; i++) {
				OLED_DrawPoint(i, 47 - AD_Value[i] / 103);
				MinVol = MinVol < AD_Value[i] ? MinVol : AD_Value[i];
				MaxVol = MaxVol > AD_Value[i] ? MaxVol : AD_Value[i];
			}
			OLED_ShowNum(58, 54, MaxVol / 1241, 1, 6);
			OLED_ShowNum(70, 54, MaxVol / 124 % 10, 1, 6);
			OLED_ShowNum(94, 54, MinVol / 1241, 1, 6);
			OLED_ShowNum(106, 54, MinVol / 124 % 10, 1, 6);
			AD_SetIntervalTime(Freq);
			OLED_Update();
		}
		if (Key_Scan()) {
			if (KeyState[0] & 1) {
				Freq++;
			}
			if (KeyState[0] & 2) {
				Freq--;
			}
			OLED_ShowNum(0, 48, Freq, 4, 8);
			OLED_Update();
			Delay_ms(1);
		}
	}
}
