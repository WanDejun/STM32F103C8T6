#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Delay.h"
#include "MySPI.h"
#include "TIM.h"
#include "LED.h"

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	MySPI_Init();
	LED_Init();
}

int main(void) {
	Init();
	while (1) {
		OLED_ShowHexNum(1, 1, Data[0], 2);
		OLED_ShowHexNum(1, 4, Data[1], 2);
		OLED_ShowHexNum(1, 7, Data[2], 2);
		OLED_ShowHexNum(1, 10, Data[3], 2);
		OLED_ShowHexNum(2, 1, Data[4], 2);
		OLED_ShowHexNum(2, 4, Data[5], 2);
		OLED_ShowHexNum(2, 7, Data[6], 2);
		OLED_ShowHexNum(2, 10, Data[7], 2);
		OLED_ShowHexNum(3, 1, Data[8], 2);
		OLED_ShowHexNum(3, 4, Data[9], 2);
		OLED_ShowHexNum(3, 7, Data[10], 2);
		OLED_ShowHexNum(3, 10, Data[11], 2);
		OLED_ShowHexNum(4, 1, Data[12], 2);
		
		OLED_ShowNum(4, 10, Cnt_Max, 2);
	}
}

