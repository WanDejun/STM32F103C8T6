#include "stm32f10x.h"                  /* Device header */
#include "MatrixKeyBoard.h"
#include "OLED.h"
#include "Delay.h"

static void Init(void) {
	OLED_Init();
	MatrixKeyBoard_Init();
}

int main(void) {
	Init();
	OLED_ShowString(1, 1, "1- 8:");
	OLED_ShowString(2, 1, "9-10:");
	
	while (1) {
		MatrixKeyBoard_Scan();
		MatrixKeyBoard_Output();
		
		OLED_ShowBinNum(1, 6, Buffer1[0], 8);
		OLED_ShowBinNum(2, 6, Buffer1[1], 8);
		Delay_ms(1);
	}
}
 
