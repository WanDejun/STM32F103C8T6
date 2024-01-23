#include "stm32f10x.h"                  // Device header
#include "async.h"
#include "PriorityQueue.h"
#include "VisualFunction.h"
#include "MyRTC.h"

PriorityQueue_t TransactionQueue;
static PriorityQueue_Node_t node;

void async_Init(void) {
	PriorityQueue_Init(&TransactionQueue);
}

uint8_t async_Call(void) {
	if (TransactionQueue.size == 0) return 0;
	if (MyRTC_GetTime() >= PriorityQueue_Top(&TransactionQueue)->time) {
		node = *PriorityQueue_Top(&TransactionQueue);
		PriorityQueue_Pop(&TransactionQueue);
		VisualFunctionCall(&node.vFunc);
	}
	return 1;
}

void async_AddTransaction(VisualFuntion_t* vFunc, uint16_t delayTime) {
	node.time = MyRTC_GetTime() + (delayTime * 32.768);
	node.vFunc = *(vFunc);
	PriorityQueue_Insert(&TransactionQueue, &node);
}
