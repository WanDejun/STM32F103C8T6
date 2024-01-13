#include "MyRTC.h"
#include "stm32f10x.h"                  // Device header
#include "Time.h"

struct tm time_date = {};

void MyRTC_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xAA) {
		RCC_LSEConfig(RCC_LSE_ON);
		
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // 开启时钟
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		RTC_SetPrescaler(32758 - 1);
		RTC_WaitForLastTask();
		
		RTC_SetCounter(1704559300);
		RTC_WaitForLastTask();
		
		BKP_WriteBackupRegister(BKP_DR1, 0xAA);
	}
	else {
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}

uint32_t MyRTC_GetTime(void) {
	return RTC_GetCounter();
}
