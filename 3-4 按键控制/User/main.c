#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "LED.h"
#include "key.h"

uint8_t Key_Num;

int main(void) {
	LED_Init();
	Key_Init();
	
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
			break;
		}
	}
}
 
