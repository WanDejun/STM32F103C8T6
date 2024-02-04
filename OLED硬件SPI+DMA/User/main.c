#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	
	uint16_t i = 0;
	
	while (1) {
		/*测试帧率**************************/
		OLED_ShowNum(0, 0, i, 5, 8);
		OLED_ShowNum(88, 16, i, 5, 8);
		// OLED_ShowNum(88, 48, DMA_GetCurrDataCounter(DMA1_Channel3), 5, 8);
		OLED_Update();
		i++;
		/***********************************/
	}
}
