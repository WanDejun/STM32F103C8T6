#include "stm32f10x.h"                  // Device header
#include "My_i2c.h"
#include "Delay.h"

#define SCL_PORT 		GPIOB
#define SCL_PIN 		GPIO_Pin_10
#define SDA_PORT		GPIOB
#define SDA_PIN  		GPIO_Pin_11

static void SCL_high() 		{GPIO_SetBits(SCL_PORT, SCL_PIN);Delay_us(10);}
static void SCL_low()			{GPIO_ResetBits(SCL_PORT, SCL_PIN);Delay_us(10);}
static void SDA_high()			{GPIO_SetBits(SDA_PORT, SDA_PIN);Delay_us(10);}
static void SDA_low()		  	{GPIO_ResetBits(SDA_PORT, SDA_PIN);Delay_us(10);}

static uint8_t SCL_Read()		{uint8_t t = GPIO_ReadInputDataBit(SCL_PORT, SCL_PIN); Delay_us(10); return t;}
static uint8_t SDA_Read()		{uint8_t t = GPIO_ReadInputDataBit(SDA_PORT, SDA_PIN); Delay_us(10); return t;}

void My_i2c_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //开漏输出，既能输入也能输出，主机出入高电平(浮空)时即可检测外部低电平
	GPIO_InitStructure.GPIO_Pin = SCL_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCL_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;
	GPIO_Init(SDA_PORT, &GPIO_InitStructure);
	
	GPIO_SetBits(SCL_PORT, SCL_PIN);
	GPIO_SetBits(SDA_PORT, SDA_PIN);
}

void My_i2c_Start(void) {
	SDA_high();
	SCL_high();
	
	SDA_low();
	SCL_low();
}

void My_i2c_Stop(void) {
	SDA_low();
	SCL_high();
	SDA_high();
}

void My_i2c_SendByte(uint8_t Byte) {
	uint8_t loc = 0x80;
	while (loc > 0) {
		if (Byte & loc) SDA_high();
		else SDA_low();
			
		SCL_high();
		Delay_us(10);
		SCL_low();
		loc >>= 1;
	}
}

uint8_t My_i2c_ReceiveByte(void) {
	uint8_t Byte = 0x00, loc = 0x80;
	SDA_high();
	while (loc > 0) {
		SCL_high();
		if (SDA_Read() == 1) Byte |= loc;
		loc >>= 1;
		SCL_low();
	}
	return Byte;
}

void My_i2c_SendAck(uint8_t AckByte) {
	if (AckByte) SDA_high();
	else SDA_low();
		
	SCL_high();
	Delay_us(10);
	SCL_low();
}

uint8_t My_i2c_ReceiveAck(void) {
	uint8_t AckByte = 0x00;
	SDA_high();
	SCL_high();
	AckByte = SDA_Read();
	SCL_low(); 
	return AckByte;
}
