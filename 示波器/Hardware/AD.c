#include "AD.h"
#include "TIM4.h"
#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[128];
uint8_t AD_FinishFlag;

static void MyADC1_Init() {	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_1Cycles5); //ADC的任务菜单
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //独立ADC
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 对齐模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_0); // ADC模拟看门狗初始化
	ADC_AnalogWatchdogThresholdsConfig(ADC1, 2000, 0);
	ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_SingleRegEnable);
	
	// ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE); // ADC中断通道开启

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn; // ADC中断优先级配置
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

static void MyDMA_Channel1_Init() {	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize = 0; //DMA菜单中的任务数量
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE); // DMA传输完成中断开启
	
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn; // DMA1_Channel1中断优先级配置
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
	
	// DMA_Cmd(DMA1_Channel1, ENABLE);  在模拟看门狗中或AD_Start函数中重装DMA计数器并开启DMA
}

void AD_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	MyDMA_Channel1_Init();
	MyADC1_Init();
}

void ADC1_2_IRQHandler(void) { 
	if (ADC_GetITStatus(ADC1, ADC_IT_AWD) == SET) { // 模拟看门狗启动DMA
		ADC_ITConfig(ADC1, ADC_IT_AWD, DISABLE); // 关闭中断
		ADC_ClearFlag(ADC1,ADC_FLAG_AWD);
		ADC_ClearITPendingBit(ADC1, ADC_IT_AWD); // 清除标志位
		
		DMA_Cmd(DMA1_Channel1, DISABLE);
		DMA_SetCurrDataCounter(DMA1_Channel1, 128);
		DMA_Cmd(DMA1_Channel1, ENABLE);
	}
}

void DMA1_Channel1_IRQHandler(void) {
	if (DMA_GetITStatus(DMA1_IT_TC1)) {
		AD_FinishFlag = 1;
		DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
}

void AD_AutoTrigger(void) { // 看门狗自动触发
	ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);
	ADC_ClearFlag(ADC1,ADC_FLAG_AWD);
}

void AD_SetIntervalTime(uint16_t time) { // 设置触发时间间隔
	TIM4_SetTime(time);
}

uint16_t AD_GetIntervalTime(void) { // 获取触发时间间隔
	return TIM4_GetTime();
}

void AD_TimingTriggerStart(void) { // 手动开启DMA
	TIM4_Start();
}

void AD_TimingTriggerStop(void) { // 手动开启DMA
	TIM4_Stop();
}

uint8_t AD_GetFinishFlag(void) { // 获取AD数据采集完成标志位
	if (AD_FinishFlag) {
		AD_FinishFlag = 0;
		return 1;
	}
	else return 0;
}
