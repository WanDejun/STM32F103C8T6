#include "stm32f10x.h"                  // Device header
#include "PriorityQueue.h"

/************************************************
@函数功能: 优先队列初始化
@返回值: void
@参数: priorityqueue,优先队列(地址)
************************************************/
void PriorityQueue_Init(PriorityQueue_t* priorityqueue) {
	priorityqueue->size = 0;
}

/************************************************
@函数功能: 优先队列Adjust
@返回值: void
@参数: priorityqueue,优先队列(地址)
************************************************/
static void PriorityQueue_Adjust(PriorityQueue_t* priorityqueue, uint16_t loc) {
	if (loc > (priorityqueue->size >> 1)) return;
	uint16_t t = loc << 1;
	if ((t | 1) <= priorityqueue->size && priorityqueue->Tree[t | 1].time < priorityqueue->Tree[t].time) {
		t |= 1;
	}
	if (priorityqueue->Tree[t].time < priorityqueue->Tree[loc].time) {
		PriorityQueue_Node_t temp;
		temp = priorityqueue->Tree[t];
		priorityqueue->Tree[t] = priorityqueue->Tree[loc];
		priorityqueue->Tree[loc] = temp;
		PriorityQueue_Adjust(priorityqueue, t);
	}
}

/************************************************
@函数功能: 优先队列插入
@返回值: void
@参数: priorityqueue,优先队列(地址)		priorityqueue_node:新增节点
************************************************/
void PriorityQueue_Insert(PriorityQueue_t* priorityqueue, PriorityQueue_Node_t* priorityqueue_node) {
	uint16_t loc = priorityqueue->size + 1;
	priorityqueue->Tree[loc] = *(priorityqueue_node);
	
	while (loc != 1) {
		if (priorityqueue->Tree[loc].time < priorityqueue->Tree[loc >> 1].time) { 
			PriorityQueue_Node_t temp;
			temp = priorityqueue->Tree[loc >> 1];
			priorityqueue->Tree[loc >> 1] = priorityqueue->Tree[loc];
			priorityqueue->Tree[loc] = temp;
			loc >>= 1;
		}
		else 
			break;
	}
	priorityqueue->size++;
}

/************************************************
@函数功能: 查看优先队列堆顶元素
@返回值: 对顶元素节点指针
@参数: priorityqueue,优先队列(地址)
************************************************/
PriorityQueue_Node_t* PriorityQueue_Top(PriorityQueue_t* priorityqueue) {
	return (priorityqueue->Tree) + 1;
}

/************************************************
@函数功能: 优先队列弹出堆顶元素
@返回值: void
@参数: priorityqueue,优先队列(地址)
************************************************/
void PriorityQueue_Pop(PriorityQueue_t* priorityqueue) {
	priorityqueue->Tree[1] = priorityqueue->Tree[priorityqueue->size];
	priorityqueue->size--;
	PriorityQueue_Adjust(priorityqueue, 1);
}
