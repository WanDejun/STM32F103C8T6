#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "Key.h"
/***************************************************************************
KeyNum: 键码
获取当前按下的键码, 下降沿中断表示按下按键, 上升沿中断表示松开按键
***************************************************************************/
struct Key_Msg KeyMsg;

void Key_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; //引脚定义
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置EXTI
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC中断
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	
	KeyMsg.KeyCode = 0xff; //默认值，表示没有按键被按下
	KeyMsg.KeyHold = 0;
}

struct Key_Msg Key_GetNum(void) {
	return KeyMsg;
}

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) == SET) {
		Delay_ms(10);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == RESET) { //下降沿
			KeyMsg.KeyCode = 0;
			KeyMsg.KeyHold = 1;
		}
		else if (KeyMsg.KeyCode == 0) { //下降沿
			KeyMsg.KeyHold = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line1) == SET) {
		Delay_ms(10);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == RESET) { //下降沿
			KeyMsg.KeyCode = 1;
			KeyMsg.KeyHold = 1;
		}
		else if (KeyMsg.KeyCode == 1) { //下降沿
			KeyMsg.KeyHold = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line2) == SET) {
		Delay_ms(10);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == RESET) { //下降沿
			KeyMsg.KeyCode = 2;
			KeyMsg.KeyHold = 1;
		}
		else if (KeyMsg.KeyCode == 2) { //下降沿
			KeyMsg.KeyHold = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI3_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line3) == SET) {
		Delay_ms(10);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == RESET) { //下降沿
			KeyMsg.KeyCode = 3;
			KeyMsg.KeyHold = 1;
		}
		else if (KeyMsg.KeyCode == 3) { //下降沿
			KeyMsg.KeyHold = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}
