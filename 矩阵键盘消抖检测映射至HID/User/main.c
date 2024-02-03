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
	
	while (1) {
		MatrixKeyBoard_Scan();
		
//		OLED_ShowBinNum(1, 1, MatrixKeyBoard_State[0], 8);
//		OLED_ShowBinNum(2, 1, MatrixKeyBoard_State[1], 8);

		OLED_ShowBinNum(1, 1, MatrixKeyBoard_Code[8], 8);
		OLED_ShowBinNum(1, 9, MatrixKeyBoard_Code[9], 8);
		OLED_ShowBinNum(2, 1, MatrixKeyBoard_Code[10], 8);
		OLED_ShowBinNum(2, 9, MatrixKeyBoard_Code[11], 8);
		OLED_ShowBinNum(3, 1, MatrixKeyBoard_Code[12], 8);
		OLED_ShowBinNum(3, 9, MatrixKeyBoard_Code[13], 8);
		OLED_ShowBinNum(4, 1, MatrixKeyBoard_Code[14], 8);
		OLED_ShowBinNum(4, 9, MatrixKeyBoard_Code[14], 8);
		Delay_ms(10);
	}
}
 
