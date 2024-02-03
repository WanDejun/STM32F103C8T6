#include "stm32f10x.h"                  /* Device header */
#include "74HC595.h"

static void Init(void) {
	_74HC595_Init();
}

int main(void) {
	Init();
	
	_74HC595_Write(0x03);
	
	while (1) {
		;
	}
}
 
