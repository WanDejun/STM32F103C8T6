#ifndef __MYRTC_H
#define __MYRTC_H

void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);
extern uint16_t MyRTC_Time[];

#endif
