#ifndef __MATRIX_KEY_BOARD_H
#define __MATRIX_KEY_BOARD_H
#include "stm32f10x.h"                  // Device header

void MatrixKeyBoard_Init(void);
void MatrixKeyBoard_Scan(void);
uint8_t MatrixKeyBoard_Output(void);
extern uint8_t MatrixKeyBoard_State[], Buffer1[];

#endif
