#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"

void Init(void) {
	LED_Init();
}

int main(void) {
	Init();
	int i;
	
	for (i = 0; 1; i++, i %= 4) {
		switch (i) {
		case 0:
			LED_ON(GPIO_Pin_0);
			LED_OFF(GPIO_Pin_3);
			break;
		case 1:
			LED_ON(GPIO_Pin_1);
			LED_OFF(GPIO_Pin_0);
			break;
		case 2:
			LED_ON(GPIO_Pin_2);
			LED_OFF(GPIO_Pin_1);
			break;
		case 3:
			LED_ON(GPIO_Pin_3);
			LED_OFF(GPIO_Pin_2);
			break;
		}
		Delay_ms(500);
	}
	
	return 0;
}
