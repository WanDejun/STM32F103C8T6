#include "stm32f10x.h"                  // Device header
#include "MyFLASH.h"

#define STORE_START_ADDRESS				0x0800FC00
#define STORE_COUNT						512

uint16_t Store_Data[STORE_COUNT];

void Store_Init(void) {
	uint16_t i;
	if (MyFLASH_ReadHalfWord(STORE_START_ADDRESS) != 0xA5A5) {
		MyFLASH_ErasePage(STORE_START_ADDRESS);
		MyFLASH_ProgramHalfWord(0x00FC00, 0xA5A5);
		for (i= 1; i < STORE_COUNT; i++) {
			MyFLASH_ProgramHalfWord(STORE_START_ADDRESS + i * 2, 0x0000);
		}
		Store_Data[0] = 0xA5A5;
	}
	else {
		for (i = 0; i < STORE_COUNT; i++) {
			Store_Data[i] = MyFLASH_ReadHalfWord(STORE_START_ADDRESS + i * 2);
		}
	}
}

void Store_Save(void) {
	MyFLASH_ErasePage(STORE_START_ADDRESS);
	uint16_t i;
	for (i = 0; i < STORE_COUNT; i++) {
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS + i * 2, Store_Data[i]);
	}
}

void Store_Clear(void) {
	uint16_t i;
	for (i = 1; i < STORE_COUNT; i++) {
		Store_Data[i] = 0;
	}
	Store_Save();
}
