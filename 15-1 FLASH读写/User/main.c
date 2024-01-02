#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Store.h"
#include "Key.h"

uint16_t Key_Num;


static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	Key_Init();
	OLED_Init();
	Store_Init();
}

int main(void) {
	Init();

	while (1) {
		uint8_t KeyNum = Key_GetNum();
		
		if (KeyNum == 1) {
			Store_Data[1]++;
		}
		if (KeyNum == 2) {
			Store_Data[2]++;
		}
		Store_Save();
		
		OLED_ShowNum(1, 1, Store_Data[1], 5);
		OLED_ShowNum(1, 7, Store_Data[2], 5);
	}
}
 
