#include "Timer.h"
#include "stm32f10x.h"                  // Device header

extern uint16_t num;

void Timer_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2); //时钟信号源
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //输入滤波器的采样倍率
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //计数方式
	TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1; //自动重装器的默认值(计数器的上限)
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1; //PSC预分频器的值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; //重复计数器的值
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//TIM_TimeBaseInit时会默认执行一次TIM_FLAG_Update中断来写入新数据，这样会导致中断函数被执行了一次
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); 
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //设置中断信号，将TIM2拨到TIM_IT_Update上
	
	NVIC_InitTypeDef NVIC_InitStruct; //设置中断，NVIC就是叫号器
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM2, ENABLE); //开启TIM2计时器
}
