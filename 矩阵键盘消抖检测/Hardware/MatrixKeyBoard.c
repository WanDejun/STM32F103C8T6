#include "MatrixKeyBoard.h"
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define Line_Cnt		4
#define Column_Cnt		4
#define	Key_Cnt			Line_Cnt * Column_Cnt

#define Line1_Pin		GPIO_Pin_4
#define Line2_Pin		GPIO_Pin_5
#define Line3_Pin		GPIO_Pin_6
#define Line4_Pin		GPIO_Pin_7
	
#define Column1_Pin 	GPIO_Pin_3
#define Column2_Pin 	GPIO_Pin_2
#define Column3_Pin 	GPIO_Pin_1
#define Column4_Pin 	GPIO_Pin_0

uint16_t Line_Pin[Line_Cnt] = { Line1_Pin, Line2_Pin, Line3_Pin, Line4_Pin };
uint16_t Column_Pin[Column_Cnt] = { Column1_Pin, Column2_Pin, Column3_Pin, Column4_Pin };

uint8_t Buffer0[(Key_Cnt >> 3) + 1], Buffer1[(Key_Cnt >> 3) + 1], MatrixKeyBoard_State[Key_Cnt >> 3], MatrixKeyBoard_Delay[Line_Cnt][Column_Cnt], BufferFlag = 0;

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

uint8_t MatrixKeyBoard_Output(void) { // 将双缓冲区的值进行处理, 输出到MatrixKeyBoard_State中, 并更新MatrixKeyBoard_Delay等待帧
	uint8_t i, j, mask, flag, diff;
	for (i = 0; i < (Key_Cnt >> 3) + 1; i++) {
		mask = ~(Buffer0[i] ^ Buffer1[i]); // 取掩码,滤除杂波
		diff = (mask & Buffer0[i]) ^ (MatrixKeyBoard_State[i] & mask);
		if (diff) {
			flag = 1;	
			MatrixKeyBoard_State[i] = (MatrixKeyBoard_State[i] & ~mask) | (Buffer0[i] & mask);
			for (j = 0; j < 8; j++, diff >>= 1) {
				if (diff & 1) {
					MatrixKeyBoard_Delay[((i << 3) + j) / Column_Cnt][((i << 3) + j) % Column_Cnt] = 10;
				}
				
			}
		}
	}
	return flag;
}

void MatrixKeyBoard_Scan(void) {
	uint8_t i, j;
	uint16_t data;
	for (i = 0; i < Line_Cnt; i++) {
		GPIO_ResetBits(GPIOA, Line_Pin[i]);
		Delay_us(2); // 防止按键的电容效应(?
		for (j = 0; j < Column_Cnt; j++) {
			if (MatrixKeyBoard_Delay[i][j]) { MatrixKeyBoard_Delay[i][j]--; continue; } // 延迟降噪
			data = GPIO_ReadInputData(GPIOA);
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
	MatrixKeyBoard_Output();
}
