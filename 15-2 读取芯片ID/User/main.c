#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"

uint16_t Key_Num;


static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	OLED_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "F_SIZE:");
	OLED_ShowHexNum(1, 8, *((__IO uint16_t*)(0x1FFFF7E0)), 4);;
	OLED_ShowString(2, 1, "UID:");
	OLED_ShowHexNum(2, 6, *((__IO uint16_t*)(0x1FFFF7E8)), 4);
	OLED_ShowHexNum(2, 11, *((__IO uint16_t*)(0x1FFFF7E8 + 0x02)), 4);
	OLED_ShowHexNum(3, 1, *((__IO uint32_t*)(0x1FFFF7E8 + 0x04)), 8);
	OLED_ShowHexNum(4, 1, *((__IO uint32_t*)(0x1FFFF7E8 + 0x08)), 8);
	
	while (1) {

	}
}
 
