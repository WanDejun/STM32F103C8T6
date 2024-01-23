#include "stm32f10x.h"                  // Device header
#include "LED.h"

void Init(void) {
	LED_Init();
}

int main(void) {
	Init();
	
	LED_ON(GPIO_Pin_0);
	
	while (1);
	
	return 0;
}
