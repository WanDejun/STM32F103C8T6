#ifndef __KEY_H
#define __KEY_H

struct Key_Msg {
	uint8_t KeyHold;
	uint8_t KeyCode;
};
void Key_Init(void);
struct Key_Msg Key_GetNum(void);

#endif
