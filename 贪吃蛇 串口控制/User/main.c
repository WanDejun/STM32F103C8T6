#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "sys.h"
#include "pic.h"
#include "SnakeGame.h"
#include "Key.h"
#include "lcd_init.h"
#include "lcd.h"
#include "MyRTC.h"
#include "Store.h"

void Init(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Key_Init();
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	MyRTC_Init();
	Store_Init();
}

int main(void) {
	Init();
	
	while(1) {
		SnackMain();
		//LCD_ShowIntNum(10, 10, Key_GetNum(), 3, WHITE, BLACK, 12);
	}
}

