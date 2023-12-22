#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "stdio.h"

const uint16_t Array_Size = 4;
uint8_t Array[Array_Size] = {'a', 'b', 'c', 'd'};

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	OLED_Init();
	Serial_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "YYFNB!");
	
	Serial_Printf("Hello World! %d%d\n", 1, 2);
	//Serial_SendString("Hello World!");
	//Serial_SendArray(Array, Array_Size);
	//Serial_SendNum(123, 4);
	//Serial_SendByte('\n');
	
	while (1) {
		
	}
}
