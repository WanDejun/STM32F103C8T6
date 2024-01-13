#include "W25Q64.h"
#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

void W25Q64_Init(void) {
	MySPI_Init();
}

static void W25Q64_WaitBusy(void) {
	uint32_t Timeout = 50000;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) && Timeout) Timeout--;
	MySPI_Stop();
}

void W25Q64_WriteEnable(void) {
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t ArraySize) {
	W25Q64_WaitBusy();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	
	MySPI_SwapArray(DataArray, ArraySize);
	
	MySPI_Stop();
}

void W25Q64_SetErase(uint32_t Address) {
	W25Q64_WaitBusy();
	
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	MySPI_Stop();
}

void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t ArraySize) {
	W25Q64_WaitBusy();
	
	W25Q64_WriteEnable();
	
	MySPI_Start();
	
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM); //发送页编辑指令
	MySPI_SwapByte(Address >> 16); //发送地址
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	
	MySPI_SwapArray(DataArray, ArraySize);
	
	MySPI_Stop();
}
