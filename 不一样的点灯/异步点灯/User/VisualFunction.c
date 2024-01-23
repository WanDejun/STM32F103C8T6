#include "stm32f10x.h"                  // Device header
#include "VisualFunction.h"

void* VisualFunctionCall(VisualFuntion_t* vFunc) {
	return vFunc->vFunc(&vFunc->parma);
}
