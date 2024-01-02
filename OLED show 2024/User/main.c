#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Image1.h"

extern uint8_t OLED_DisplayBuf[8][128];

int main(void) {
	OLED_Init();

	uint8_t i, j;
	
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 128; j++) {
			OLED_DisplayBuf[i][j] = Image1[i * 128 + j];
		}
	}
	
	/*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
	OLED_Update();
	
	while (1) {
		/*延时1000ms，观察现象*/
		Delay_ms(1000);
	}
}
