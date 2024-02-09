#ifndef __KEY_BOARD_MAP_CONFING_H
#define __KEY_BOARD_MAP_CONFING_H
#include "stm32f10x.h"                  // Device header
#include "KeyBoardUsegeTable.h"

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

extern uint16_t Line_Pin[Line_Cnt];
extern uint16_t Column_Pin[Column_Cnt];

extern uint8_t KeyBoardMapMatrix[Line_Cnt][Column_Cnt];

#endif
