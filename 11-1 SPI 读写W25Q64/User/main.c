#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"
#include "Delay.h"

uint8_t ArrayWrite[12] = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33}, ArrayReceive[12] = {};

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
	W25Q64_Init();
}

int main(void) {
	Init();
	
	uint8_t MID;
	uint16_t DID;
	
	OLED_ShowString(1, 1, "MID:   DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	
	W25Q64_ReadID(&MID, &DID);
	
	W25Q64_SetErase(0x00000000);
	W25Q64_PageProgram(0x000000, ArrayWrite, 12);
	W25Q64_ReadData(0x000000, ArrayReceive, 12);
	
	uint8_t i;
	
	while (1) {
		OLED_ShowHexNum(1, 5, MID, 2);
		OLED_ShowHexNum(1, 12, DID, 4);
		
		for (i = 0; i < 12; i++) {
			OLED_ShowChar(2, 3 + i, ArrayWrite[i]);
			OLED_ShowChar(3, 3 + i, ArrayReceive[i]);
		}
		
	}
}
 
