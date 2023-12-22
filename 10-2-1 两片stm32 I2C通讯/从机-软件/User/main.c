#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "MyI2C.h"

uint16_t Key_Num;

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	MyI2C_Init();
}

int main(void) {
	Init();
	
	while (1) {
		OLED_ShowHexNum(1, 1, Rx_Data[0], 2);
		OLED_ShowHexNum(2, 1, Rx_Data[1], 2);
	}
}
 
