#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "sys.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"

int main(void)
{
	float t=0;
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	
	while(1)
	{
		LCD_ShowString(24,30,(uint8_t*)"LCD_W:",WHITE,BLUE,16,1);
		LCD_ShowIntNum(72,30,LCD_W,3,WHITE,BLACK,16);
		LCD_ShowString(24,50,(uint8_t*)"LCD_H:",WHITE,BLACK,16,0);
		LCD_ShowIntNum(72,50,LCD_H,3,WHITE,BLACK,16);
		LCD_ShowFloatNum1(20,80,t,4,WHITE,BLACK,16);
		t += 0.11;
		LCD_ShowPicture(65,80,40,40,gImage_1);
	}
}

