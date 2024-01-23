#ifndef __VISUAL_FUNCTION_H
#define __VISUAL_FUNCTION_H
#include "stm32f10x.h"                  // Device header

typedef struct { // 虚函数参数列表结构体
	uint16_t ui16_A;
} Parma;

typedef struct { // 虚函数结构体
	Parma parma;
	void* (*vFunc)(Parma*);
} VisualFuntion_t;

void* VisualFunctionCall(VisualFuntion_t* vFunc);

#endif
