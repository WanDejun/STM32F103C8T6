#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Serial.h"
#include "string.h"

uint16_t Key_Num;


static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	LED_Init();
	Serial_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "TX:");
	OLED_ShowString(3, 1, "RX:");
	
	while (1) {
		if (Serial_GetRxFlag()) {
			OLED_ShowString(4, 1, "               ");
			OLED_ShowString(4, 1, (char *)Serial_RxPacket);
			
			if (strcmp("LED_ON!", (char *)Serial_RxPacket) == 0) {
				LED_set(GPIO_Pin_1, Bit_RESET);
				OLED_ShowString(2, 1, "Accept:LED_ON! ");
				Serial_SendPacket("Accept:LED_ON!\n");
			}
			else if (strcmp("LED_OFF!", (char *)Serial_RxPacket) == 0) {
				LED_set(GPIO_Pin_1, Bit_SET);
				OLED_ShowString(2, 1, "Accept:LED_OFF! ");
				Serial_SendPacket("Accept:LED_OFF!\n");
			}
			else {
				OLED_ShowString(2, 1, "Error!        ");
				Serial_SendPacket("Error!\n");
			}
		}
	}
}

