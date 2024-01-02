#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

uint16_t Key_Num;


static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
	MyRTC_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Date:xxxx-xx-xx");
	OLED_ShowString(2, 1, "Time:xx-xx-xx");
	OLED_ShowString(3, 1, "CNT:");
	//OLED_ShowString(4, 1, "DIV:");
	
	while (1) {
		MyRTC_ReadTime();
		OLED_ShowNum(1, 6, MyRTC_Time[0], 4);
		OLED_ShowNum(1, 11, MyRTC_Time[1], 2);
		OLED_ShowNum(1, 14, MyRTC_Time[2], 2);
		OLED_ShowNum(2, 6, MyRTC_Time[3], 2);
		OLED_ShowNum(2, 9, MyRTC_Time[4], 2);
		OLED_ShowNum(2, 12, MyRTC_Time[5], 2);
		
		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);
		
		//OLED_ShowNum(4, 6, RTC_GetDivider(), 10);
	}
}
