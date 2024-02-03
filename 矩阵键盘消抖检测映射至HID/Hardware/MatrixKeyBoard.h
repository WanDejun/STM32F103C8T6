#ifndef __MATRIX_KEY_BOARD_H
#define __MATRIX_KEY_BOARD_H
#include "stm32f10x.h"                  // Device header

void MatrixKeyBoard_Init(void);
uint8_t MatrixKeyBoard_Scan(void);
extern uint8_t MatrixKeyBoard_Code[], MatrixKeyBoard_State[];

#endif
