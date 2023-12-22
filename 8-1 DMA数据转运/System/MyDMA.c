#include "stm32f10x.h"                  // Device header
#include "MyDMA.h"

static uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t Addr_A, uint32_t Addr_B, uint16_t size) {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	MyDMA_Size = size;
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize = MyDMA_Size; // 传输次数
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // 传输方向 外设站点作为SRC或DST
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable; //存储器到存储器(软件触发)
	
	DMA_InitStructure.DMA_MemoryBaseAddr = Addr_B; //存储器(终)
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//自动重装关
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = Addr_A; // 外设(源)
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //优先级
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
}

void MyDMA_Transfer() {
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); 
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
