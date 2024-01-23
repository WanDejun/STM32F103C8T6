#ifndef __PRIORITY_QUEUE_H
#define __PRIORITY_QUEUE_H
#include "stm32f10x.h"                  // Device header
#include "VisualFunction.h"
#define PRIORITY_QUEUE_MAX_SIZE 8

typedef struct {
	uint64_t time; // 时间戳
	VisualFuntion_t vFunc; // 虚函数结构体
} PriorityQueue_Node_t; // 优先队列节点结构体

typedef struct {
	uint16_t size;
	PriorityQueue_Node_t Tree[PRIORITY_QUEUE_MAX_SIZE];
} PriorityQueue_t; // 优先队列结构体

void PriorityQueue_Init(PriorityQueue_t* priorityqueue);
void PriorityQueue_Insert(PriorityQueue_t* priorityqueue, PriorityQueue_Node_t* priorityqueue_node);
PriorityQueue_Node_t* PriorityQueue_Top(PriorityQueue_t* priorityqueue);
void PriorityQueue_Pop(PriorityQueue_t* priorityqueue);

#endif
