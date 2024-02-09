#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Image1.h"
#include "Key.h"

extern uint8_t OLED_DisplayBuf[8][128];
uint8_t Image2[1024];

uint8_t offset = 0;

void Init(void) {
	OLED_Init();
	Key_Init();
	uint16_t i, j, offset = 0;
	
	for (i = 0; i < 64; i++) {
		for (j = 0; j < 96 - i; j++) {
			Image2[(i >> 3) * 128 + j] |= 1 << (i & 0x07);
		}
	}
}

void Render(void) {
	uint16_t i, j;
	
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 128; j++) {
			OLED_DisplayBuf[i][j] = Image2[(i << 7) + j] ^ Image1[(i << 7) + ((j + offset) & 0x7f)];
		}
	}
	OLED_Update();
}

int main(void) {
	Init();
	Render();
	
	while (1) {
		Key_Scan();
		if (KeyState[0]) {
			if (KeyState[0] & 0x01) offset = (offset - 1) & 0x7f; 
			if (KeyState[0] & 0x02) offset = (offset + 1) & 0x7f;
			Render();
		}
		
		Delay_ms(10);
	}
}
