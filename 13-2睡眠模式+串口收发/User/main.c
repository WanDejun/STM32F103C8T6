#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	Serial_Init();
	OLED_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "TX:");
	OLED_ShowString(3, 1, "RX:");
	
	while (1) {
		if (Serial_GetRxFlag()) {
			OLED_ShowString(4, 1, "               ");
			OLED_ShowString(4, 1, (char *)Serial_RxPacket);
			
			OLED_ShowString(2, 1, "               ");
			OLED_ShowString(2, 1, (char *)Serial_RxPacket);
			Serial_SendPacket((char *)Serial_RxPacket);
		}
		OLED_ShowString(1, 5, "Runing");
		Delay_ms(200);
		OLED_ShowString(1, 5, "      ");
		Delay_ms(200);
		
		__WFI();
	}
	
}
 
