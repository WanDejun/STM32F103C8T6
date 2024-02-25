#include "KeyBoardMapConfig.h"
#include "stm32f10x.h"                  // Device header

uint8_t KeyBoardMapMatrix[Line_Cnt][Column_Cnt] = {
	{ NUM7_HOME, 		NUM8_UP_ARROW, 		NUM9_PAGE_UP, 		NUM_DIVISION	},
	{ NUM4_LEFT_ARROW, 	NUM5, 				NUM6_RIGHT_ARROW, 	NUM_MULTIPLE	},
	{ NUM1_END, 		NUM2_DOWN_ARROW, 	NUM3_PAGE_DOWN, 	NUM_MINUS		},
	{ NUM0_INSERT, 		NUM_ENTER, 			NUM_DOT_DELETE, 	NUM_PLUS 		},
};
uint16_t Line_Pin[Line_Cnt] = { Line1_Pin, Line2_Pin, Line3_Pin, Line4_Pin };
uint16_t Column_Pin[Column_Cnt] = { Column1_Pin, Column2_Pin, Column3_Pin, Column4_Pin };
