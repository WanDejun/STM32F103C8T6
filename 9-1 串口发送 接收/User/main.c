#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "stdio.h"

const uint16_t Array_Size = 4;
uint8_t Array[Array_Size] = {'a', 'b', 'c', 'd'};
uint8_t data;

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	Serial_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "YYFNB!");
	
	Serial_Printf("Hello World! %d%d\n", 1, 2);
	
	while (1) {
		OLED_ShowHexNum(2, 1, Serial_ReceiveData, 2);
	}
}
