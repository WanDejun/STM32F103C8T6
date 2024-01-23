#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "MyRTC.h"
#include "async.h"
#include "VisualFunction.h"
#include "OLED.h"
#include "PriorityQueue.h"

extern PriorityQueue_t TransactionQueue;

VisualFuntion_t vFunc_LED0;
VisualFuntion_t vFunc_LED1;
VisualFuntion_t vFunc_LED2;
VisualFuntion_t vFunc_LED3;
VisualFuntion_t vFunc_LED4;

void* vFunc_LED(Parma* parma) {
	switch (parma->ui16_A) {
	case 0:
		LED_Flip(GPIO_Pin_0);
		async_AddTransaction(&vFunc_LED0, 1200);
		break;
	case 1:
		LED_Flip(GPIO_Pin_1);
		async_AddTransaction(&vFunc_LED1, 1000);
		break;
	case 2:
		LED_Flip(GPIO_Pin_2);
		async_AddTransaction(&vFunc_LED2, 800);
		break;
	case 3:
		LED_Flip(GPIO_Pin_3);
		async_AddTransaction(&vFunc_LED3, 600);
		break;
	case 4:
		LED_Flip(GPIO_Pin_4);
		async_AddTransaction(&vFunc_LED4, 400);
		break;
	default:
		break;
	}
	return (void*)0;
}

void Init(void) {
	LED_Init();
	MyRTC_Init();
	async_Init();
	OLED_Init();	
}

int main(void) {
	Init();
	
	vFunc_LED0.vFunc = vFunc_LED;
	vFunc_LED1.vFunc = vFunc_LED;
	vFunc_LED2.vFunc = vFunc_LED;
	vFunc_LED3.vFunc = vFunc_LED;
	vFunc_LED4.vFunc = vFunc_LED;
	
	vFunc_LED0.parma.ui16_A = 0;
    vFunc_LED1.parma.ui16_A = 1;
	vFunc_LED2.parma.ui16_A = 2;
	vFunc_LED3.parma.ui16_A = 3;
    vFunc_LED4.parma.ui16_A = 4;
	
	async_AddTransaction(&vFunc_LED0, 100);
	async_AddTransaction(&vFunc_LED1, 100);
	async_AddTransaction(&vFunc_LED2, 100);
	async_AddTransaction(&vFunc_LED3, 100);
	async_AddTransaction(&vFunc_LED4, 100);
	
	while (async_Call()) {
		OLED_ShowNum(1, 1, TransactionQueue.Tree[1].time, 12);
		OLED_ShowNum(2, 1, TransactionQueue.Tree[2].time, 12);
		OLED_ShowNum(3, 1, TransactionQueue.Tree[3].time, 12);
		OLED_ShowNum(4, 1, TransactionQueue.Tree[4].time, 12);
	}
	
	return 0;
}