#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"

static uint16_t LightSenserCnt;

void LightSenser_Init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
}

uint16_t LightSenserGetCnt(void) {
	return LightSenserCnt;
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line8) == SET) {	
		EXTI_ClearITPendingBit(EXTI_Line8);
		
		LightSenserCnt++;
	}
}

uint8_t LightSenser_Get(void) {
	return !GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_8);
}
