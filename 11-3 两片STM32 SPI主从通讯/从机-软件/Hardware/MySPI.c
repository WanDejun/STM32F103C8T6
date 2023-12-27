// MySPI.c
#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "LED.h"

#define MySPI_SLEEP 0 //状态定义
#define MySPI_START 1

// PA4: SS	PA5: SCK	PA6: MISO	P6: MOSI

#define SS_Pin GPIO_Pin_4 // 引脚定义
#define SCK_Pin GPIO_Pin_5 
#define MISO_Pin GPIO_Pin_6
#define MOSI_Pin GPIO_Pin_7

static uint8_t Count, Status, Loc;
uint8_t Data[13] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };

static uint8_t MySPI_R_SCK() { //读取时钟
	return GPIO_ReadInputDataBit(GPIOA, SCK_Pin);
}

static uint8_t MySPI_R_SS() { //读取片选
	return GPIO_ReadInputDataBit(GPIOA, SS_Pin);
}

static uint8_t MySPI_R_MOSI() { //从机读
	return GPIO_ReadInputDataBit(GPIOA, MOSI_Pin);
}

static void MySPI_W_MISO(uint8_t BitValue) { //从机写MISO
	GPIO_WriteBit(GPIOA, MISO_Pin, (BitAction)BitValue);
}

void MySPI_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //开启AFIO时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = SS_Pin | SCK_Pin | MOSI_Pin; // SS | CSK | MOSI 上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = MISO_Pin; //MISO 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4); //EXTI
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
	
	EXTI_InitTypeDef EXTI_InitSturcture; //EXTI初始化
	EXTI_InitSturcture.EXTI_Line = EXTI_Line4 | EXTI_Line5;
	EXTI_InitSturcture.EXTI_LineCmd = ENABLE;
	EXTI_InitSturcture.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSturcture.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitSturcture);
	
	NVIC_InitTypeDef NVIC_InitStructure; //中断配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
		
	Status = MySPI_SLEEP; //初始状态
}

void EXTI4_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line4)) { //SS片选
		if (!MySPI_R_SS()) { //下降沿
			Status = MySPI_START; //起始状态
			Count = Loc = 0;
			
			MySPI_W_MISO(*(Data + Loc) & 0x80); //发送数据
			*(Data + Loc) <<= 1;
		}
		else { //上升沿
			Status = MySPI_SLEEP; // 终止状态
		}
		
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line5)) {
		if (Status == MySPI_START) {
			if (!MySPI_R_SCK()) { //SCK下降沿
				MySPI_W_MISO(*(Data + Loc) & 0x80); //发送数据
				*(Data + Loc) <<= 1;
			}
			else { //SCK上升沿
				*(Data + Loc) |= MySPI_R_MOSI(); //写入数据
				Count++;
				
				if (Count == 8) {
					Count = 0;
					Loc++;
				}
			}
		}
		
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}
