#ifndef __MYRTC_H
#define __MYRTC_H
#include "stm32f10x.h"                  // Device header

void MyRTC_Init(void);
uint32_t MyRTC_GetTime(void);

#endif
