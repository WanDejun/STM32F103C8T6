#include "stm32f10x.h"                  // Device header
#include "MyRTC.h"
#include "Time.h"

uint16_t MyRTC_Time[] = { 2023, 12, 28, 3, 11, 0 };

void MyRTC_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	PWR_BackupAccessCmd(ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) == 0x00) {
		RCC_LSEConfig(RCC_LSE_ON);
			
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		RTC_SetPrescaler(32768 - 1); // 预分频器
		RTC_WaitForLastTask();
		
		RTC_SetCounter(114514); // 初始化时间
		RTC_WaitForLastTask();
		
		BKP_WriteBackupRegister(BKP_DR1, 0x01);
	}
	else {
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}

uint64_t MyRTC_GetTime(void) {
	return RTC_GetCounter() << 15 | ((1ll << 15) - ((uint16_t)RTC_GetDivider()));
}
