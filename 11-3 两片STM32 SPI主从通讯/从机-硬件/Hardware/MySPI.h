#ifndef __MYSPI_H
#define __MYSPI_H

extern uint8_t Data[13], Cnt_Send, Cnt_Receive, Cnt_Max;
void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t Byte);
void MySPI_SwapArray(uint8_t* Array, uint8_t ArraySize);

#endif 
