#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MenuControler.h"

void Init(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
}

int main(void) {
	Init();
	
	MenuMain();
	while (1) {
		;
	}
}
