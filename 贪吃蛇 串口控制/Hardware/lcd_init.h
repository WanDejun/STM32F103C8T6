#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define USE_HORIZONTAL 1  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif

//-----------------LCD端口定义---------------- 

#define SCL_Port		GPIOB
#define SDA_Port		GPIOB
#define RES_Port		GPIOB
#define DC_Port			GPIOB
#define CS_Port			GPIOB
#define BLK_Port		GPIOB

#define SCL_Pin		GPIO_Pin_5
#define SDA_Pin		GPIO_Pin_6
#define RES_Pin		GPIO_Pin_7
#define DC_Pin		GPIO_Pin_8
#define CS_Pin		GPIO_Pin_9
#define BLK_Pin		GPIO_Pin_10

#define LCD_SCLK_Clr() GPIO_ResetBits(SCL_Port,SCL_Pin)//SCL=SCLK
#define LCD_SCLK_Set() GPIO_SetBits(SCL_Port,SCL_Pin)

#define LCD_MOSI_Clr() GPIO_ResetBits(SDA_Port,SDA_Pin)//SDA=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(SDA_Port,SDA_Pin)

#define LCD_RES_Clr()  GPIO_ResetBits(RES_Port,RES_Pin)//RES
#define LCD_RES_Set()  GPIO_SetBits(RES_Port,RES_Pin)

#define LCD_DC_Clr()   GPIO_ResetBits(DC_Port,DC_Pin)//DC
#define LCD_DC_Set()   GPIO_SetBits(DC_Port,DC_Pin)
 		     
#define LCD_CS_Clr()   GPIO_ResetBits(CS_Port,CS_Pin)//CS
#define LCD_CS_Set()   GPIO_SetBits(CS_Port,CS_Pin)

#define LCD_BLK_Clr()  GPIO_ResetBits(BLK_Port,BLK_Pin)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(BLK_Port,BLK_Pin)




void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




