#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint8_t KeyNum;
uint16_t ArrayWrite[] = {0x1234, 0x5678}, ArrayRead[2];

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	
	OLED_Init();
	Key_Init();
}

int main(void) {
	Init();
	
	uint8_t i;
	
	OLED_ShowString(1, 1, "W:");
	OLED_ShowString(2, 1, "R:");
	
	while (1) {
		KeyNum = Key_GetNum();
		if (KeyNum == 1) {
			for (i = 0; i < 2; i++) {
				ArrayWrite[i]++;
				BKP_WriteBackupRegister(BKP_DR1 + 0x0004 * i, ArrayWrite[i]);
				OLED_ShowHexNum(1, 3 + 5 * i, ArrayWrite[i], 4);
			}
		}
		
		for (i = 0; i < 2; i++) {
			ArrayRead[i] = BKP_ReadBackupRegister(BKP_DR1 + i * 4);
			OLED_ShowHexNum(2, 3 + 5 * i, ArrayRead[i], 4);
		}

	}
}
 
