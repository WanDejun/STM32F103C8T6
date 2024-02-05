#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	
	uint8_t i, j, k;
	extern uint8_t OLED_DisplayBuf[8][128];
	
	while (1) {
		/*测试帧率**************************/
		for (i = 0; i < 8; i++) for (j = 0; j < 128; j++) for (k = 0; k < 8; k++) {
			OLED_DisplayBuf[i][j] |= 1 << k;
			OLED_Update();
		}
		for (j = 0; j < 128; j++) for (i = 0; i < 8; i++) for (k = 0; k < 8; k++) {
			OLED_DisplayBuf[i][j] &= ~(1 << k);
			OLED_Update();
		}
		/***********************************/
	}
}
