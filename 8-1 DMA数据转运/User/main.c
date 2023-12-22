#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"

uint8_t Data_A[] = {1, 2, 3, 4}, Data_B[4] = { };

/*PA0 接滑动变阻器中间脚
PA2接光敏电阻AD端*/

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();	
	MyDMA_Init((uint32_t)Data_A, (uint32_t)Data_B, 4);
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Data_A");
	OLED_ShowString(3, 1, "Data_B");
	OLED_ShowHexNum(1, 8, (uint32_t)Data_A, 8);
	OLED_ShowHexNum(3, 8, (uint32_t)Data_B, 8);
	
	OLED_ShowNum(2, 1, Data_A[0], 2);
	OLED_ShowNum(2, 4, Data_A[1], 2);
	OLED_ShowNum(2, 7, Data_A[2], 2);
	OLED_ShowNum(2, 10, Data_A[3], 2);
	
	OLED_ShowNum(4, 1, Data_B[0], 2);
	OLED_ShowNum(4, 4, Data_B[1], 2);
	OLED_ShowNum(4, 7, Data_B[2], 2);
	OLED_ShowNum(4, 10, Data_B[3], 2);
	
	while (1) {
		Data_A[0]++;
		Data_A[1]++;
		Data_A[2]++;
		Data_A[3]++;
		
		OLED_ShowNum(2, 1, Data_A[0], 2);
		OLED_ShowNum(2, 4, Data_A[1], 2);
		OLED_ShowNum(2, 7, Data_A[2], 2);
		OLED_ShowNum(2, 10, Data_A[3], 2);
		
		OLED_ShowNum(4, 1, Data_B[0], 2);
		OLED_ShowNum(4, 4, Data_B[1], 2);
		OLED_ShowNum(4, 7, Data_B[2], 2);
		OLED_ShowNum(4, 10, Data_B[3], 2);
		
		Delay_ms(1000);
		
		MyDMA_Transfer();
		
		OLED_ShowNum(2, 1, Data_A[0], 2);
		OLED_ShowNum(2, 4, Data_A[1], 2);
		OLED_ShowNum(2, 7, Data_A[2], 2);
		OLED_ShowNum(2, 10, Data_A[3], 2);
		
		OLED_ShowNum(4, 1, Data_B[0], 2);
		OLED_ShowNum(4, 4, Data_B[1], 2);
		OLED_ShowNum(4, 7, Data_B[2], 2);
		OLED_ShowNum(4, 10, Data_B[3], 2);
		
		Delay_ms(1000);
	}
}
 
