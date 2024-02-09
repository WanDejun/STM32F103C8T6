#include "MatrixKeyBoard.h"
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "KeyBoardMapConfig.h"

uint8_t Buffer0[(Key_Cnt + 7) >> 3], Buffer1[(Key_Cnt + 7) >> 3], MatrixKeyBoard_State[(Key_Cnt + 7) >> 3], MatrixKeyBoard_Delay[Line_Cnt][Column_Cnt], BufferFlag = 0;
uint8_t MatrixKeyBoard_Code[17];

void MatrixKeyBoard_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	uint16_t GPIO_AllPin, i;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_AllPin = 0; // 行开漏输出
	for (i = 0; i < Line_Cnt; i++) {
		GPIO_AllPin |= Line_Pin[i];
	}
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_AllPin;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_AllPin = 0;  //列上拉输入
	for (i = 0; i < Column_Cnt; i++) {
		GPIO_AllPin |= Column_Pin[i];
	}
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_AllPin;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static uint8_t MatrixKeyBoard_Output(void) { // 将双缓冲区的值进行处理, 输出到MatrixKeyBoard_State中, 并更新MatrixKeyBoard_Delay等待帧
	uint8_t i, j, mask, flag, diff, code;
	for (i = 0; i < (Key_Cnt + 7) >> 3; i++) {
		mask = ~(Buffer0[i] ^ Buffer1[i]); // 取掩码,滤除杂波
		diff = (mask & Buffer0[i]) ^ (MatrixKeyBoard_State[i] & mask);
		if (diff) {
			flag = 1; // 表示有按键事件更新
			MatrixKeyBoard_State[i] = (MatrixKeyBoard_State[i] & ~mask) | (Buffer0[i] & mask); // 更新按键状态
			for (j = 0; j < 8; j++, diff >>= 1) { 
				if (diff & 1) { // 第j位被更新
					MatrixKeyBoard_Delay[((i << 3) + j) / Column_Cnt][((i << 3) + j) % Column_Cnt] = 10; // 按键延时, 防止误触
					
					code = KeyBoardMapMatrix[((i << 3) + j) / Column_Cnt][((i << 3) + j) % Column_Cnt]; // 映射至HID键码
					if (MatrixKeyBoard_State[i] & (1 << j)) // 按下
						MatrixKeyBoard_Code[code / 8] |= 1 << (code % 8); // 置1
					else 
						MatrixKeyBoard_Code[code / 8] &= ~(1 << (code % 8)); // 置0
				}
			}
		}
	}
	return flag;
}

uint8_t MatrixKeyBoard_Scan(void) {
	uint8_t i, j;
	uint16_t data;
	for (i = 0; i < Line_Cnt; i++) {
		GPIO_ResetBits(GPIOA, Line_Pin[i]);
		Delay_us(2); // 防止按键的电容效应(?
		data = GPIO_ReadInputData(GPIOA);
		for (j = 0; j < Column_Cnt; j++) {
			if (MatrixKeyBoard_Delay[i][j]) { MatrixKeyBoard_Delay[i][j]--; continue; } // 延迟降噪
			if (BufferFlag) {
				if (data & Column_Pin[j]) Buffer1[(i * Column_Cnt + j) >> 3] &= ~(1 << ((i * Column_Cnt + j) % 8)); // 未检测到按下
				else Buffer1[(i * Column_Cnt + j) >> 3] |= 1 << ((i * Column_Cnt + j) % 8); // 检测到按下
			}
			else {
				if (data & Column_Pin[j]) Buffer0[(i * Column_Cnt + j) >> 3] &= ~(1 << ((i * Column_Cnt + j) % 8)); // 未检测到按下
				else Buffer0[(i * Column_Cnt + j) >> 3] |= 1 << ((i * Column_Cnt + j) % 8); // 检测到按下
			}
		}
		GPIO_SetBits(GPIOA, Line_Pin[i]);
		Delay_us(2); 
	}
	BufferFlag ^= 1; // 切换缓冲区
	return MatrixKeyBoard_Output();
}

