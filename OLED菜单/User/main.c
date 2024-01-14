#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

void Init(void) {
	OLED_Init();
	Encoder_Init();
}

int main(void) {
	Init();
	
	OLED_MenuAdd("Hello Menu!");
	OLED_MenuAdd("OLED UPRoll1");
	OLED_MenuAdd("UPRoll2");
	OLED_MenuAdd("OLED UPRoll3");
	OLED_MenuAdd("UPRoll4");
	OLED_MenuAdd("OLED DownRoll1");
	OLED_MenuAdd("DownRoll2");
	OLED_MenuAdd("OLED DownRoll3");
	OLED_MenuAdd("DownRoll4");
	OLED_MenuAdd("(end)");
	OLED_MenuInit();

	int16_t countPre = 0, countNxt, i;
	while (1) {
		countNxt = (TIM_GetCounter(TIM2) - 10000) / 4;

		if (countNxt - countPre > 0) {
			//for (i = 0; i < countNxt - countPre; i++) OLED_MenuDownRoll_1Px();
			OLED_MenuSelectDown();
		}
		else if (countNxt - countPre < 0) {
			//for (i = 0; i < countPre - countNxt; i++) OLED_MenuUpRoll_1Px();
			OLED_MenuSelectUp();
		}
		
		//OLED_Update();
		
		if (countNxt <= -80) countPre = countNxt + 80;
		else if (countNxt >= 80) countPre = countNxt - 80;
		else countPre = countNxt;
	}
}
