#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Image.h"
#include "W25Q64.h"
#include "Serial.h"

void Init(void) {
	OLED_Init();
	W25Q64_Init();
	Serial_Init();
}

int main(void) {
	Init();
	
	while (1) {
		if (Serial_GetRxFlag() == 1)
			Show_Image(0);
	}
}
