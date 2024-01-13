#ifndef __IMAGE_H
#define __IMAGE_H
#include "stm32f10x.h"                  // Device header

extern uint8_t Image_4[4096];
void Image_Save(uint32_t Address);
void Image_Load(uint32_t Address);
void Show_Image(uint8_t Cnt);

#endif
