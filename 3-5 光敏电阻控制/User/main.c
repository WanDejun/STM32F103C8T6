#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "LED.h"
#include "key.h"
#include "LightSenser.h"

uint16_t Key_Num;

int main(void) {
	LED_Init();
	Key_Init();
	LightSenser_Init();
	
	while (1) {
		Key_Num = Key_GetNum();
		switch (Key_Num) {
		case 1:
			LED_Flip(GPIO_Pin_3);
			break;
		case 2:
			LED_Flip(GPIO_Pin_5);
			break;
		default:
			if (LightSenser_Get() == 0) 
				LED_set(GPIO_Pin_9, Bit_SET);
			else 
				LED_set(GPIO_Pin_9, Bit_RESET);
			break;
		}
	}
}
 
