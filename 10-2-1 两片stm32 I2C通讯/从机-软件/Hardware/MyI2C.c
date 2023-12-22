#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "Delay.h"
#include "OLED.h"

#define SCL_PORT 			GPIOB
#define SCL_PIN 			GPIO_Pin_10
#define SDA_PORT 			GPIOB
#define SDA_PIN 			GPIO_Pin_11

#define SW_SLAVE_ADDR			0x0F

#define I2C_MODE_SLEEP         	0          	// Waiting for commands
#define I2C_MODE_START		   	1          	// 
#define I2C_MODE_SACK      		2          	// 
#define I2C_MODE_RACK		  	3          	// 
#define I2C_MODE_SEND  			4          	// 
#define I2C_MODE_RECEIVE  		5          	// 
#define I2C_MODE_END			6			// End

static void SCL_high() 			{GPIO_SetBits(SCL_PORT, SCL_PIN);Delay_us(10);}
static void SCL_low()			{GPIO_ResetBits(SCL_PORT, SCL_PIN);Delay_us(10);}
static void SDA_high()			{GPIO_SetBits(SDA_PORT, SDA_PIN);Delay_us(10);}
static void SDA_low()		  	{GPIO_ResetBits(SDA_PORT, SDA_PIN);Delay_us(10);}

static uint8_t SCL_Read()		{uint8_t t = GPIO_ReadInputDataBit(SCL_PORT, SCL_PIN); Delay_us(10); return t;}
static uint8_t SDA_Read()		{uint8_t t = GPIO_ReadInputDataBit(SDA_PORT, SDA_PIN); Delay_us(10); return t;}

struct _SwSlaveI2C_t
{
    uint8_t State;					// I2C通信状态
	uint8_t Rw;						// I2C读写标志：0-写，1-读
	uint8_t Cnt;					// SCL计数
	uint8_t* RxBuf;					// 指向接收缓冲区的指针
	uint8_t* TxBuf;					// 指向发送缓冲区的指针
	uint8_t RxIdx;					// 接收缓冲区数据写入索引，最大值255
	uint8_t TxIdx;					// 发送缓冲区数据读取索引，最大值255
} SwSlaveI2C;

uint8_t Rx_Data[8], Tx_Data[8] = {0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71}, Address;

void MyI2C_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;				//开漏输出
	GPIO_InitStructure.GPIO_Pin = SCL_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCL_PORT, &GPIO_InitStructure);						//初始化SCL
	
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;
	GPIO_Init(SDA_PORT, &GPIO_InitStructure);						//初始化SDA
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
	
	EXTI_InitTypeDef EXTI_InitStructure;							//定义结构体变量
	EXTI_InitStructure.EXTI_Line = EXTI_Line10 | EXTI_Line11;		//选择配置外部中断的0号线和1号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);									//将结构体变量交给EXTI_Init，配置EXTI外设
	
	NVIC_InitTypeDef NVIC_InitStructure;							//初始化中断
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
		
	Address = 0;													//读取地址暂存
	
	SCL_high();
	SDA_high();
	
	SwSlaveI2C.State = I2C_MODE_SLEEP;								//初始化通选相关的数据
	SwSlaveI2C.RxBuf = Rx_Data;
	SwSlaveI2C.RxIdx = 0;
	SwSlaveI2C.Cnt = 0;
	SwSlaveI2C.Rw = 0;
	SwSlaveI2C.TxBuf = Tx_Data;
	SwSlaveI2C.TxIdx = 0;
}

void EXTI15_10_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line10) == SET) { 		//SCL
		EXTI_ClearITPendingBit(EXTI_Line10);
		
		if (SCL_Read() == Bit_SET) { 					//SCL上升沿
			switch (SwSlaveI2C.State) {
				case I2C_MODE_START:				//起始模式下, SCL上升沿读取设备地址
					if (SwSlaveI2C.Cnt < 8) {
						Address |= ((SDA_Read() == Bit_SET ? 1 : 0) << (7 - SwSlaveI2C.Cnt));
						SwSlaveI2C.Cnt++;
					}
					break;
					
				case I2C_MODE_RACK: 			//读取应答
					if (SDA_Read() == Bit_SET) {//未应答
						SwSlaveI2C.State = I2C_MODE_END;
					}
					else {					//应答
						SwSlaveI2C.State = I2C_MODE_SEND;
					}
					break;
				
				case I2C_MODE_RECEIVE:
					if (SwSlaveI2C.Cnt < 8) {
						*(SwSlaveI2C.RxBuf + SwSlaveI2C.RxIdx) &= ~(1 << (7 - SwSlaveI2C.Cnt));
						*(SwSlaveI2C.RxBuf + SwSlaveI2C.RxIdx) |= ((SDA_Read() == Bit_SET ? 1 : 0) << (7 - SwSlaveI2C.Cnt));
						SwSlaveI2C.Cnt++;
					}
					break;
				
				default:
					break;
				
			}
		}
		else {											//SCL下降沿
			switch (SwSlaveI2C.State) {
				case I2C_MODE_START:
					if (SwSlaveI2C.Cnt != 8) return;
					SwSlaveI2C.Rw = Address & 1;	//起始模式读取完毕
					if (Address >> 1 != SW_SLAVE_ADDR) {
						SwSlaveI2C.State = I2C_MODE_SLEEP;
					}
					SwSlaveI2C.Cnt = 0;
					SwSlaveI2C.State = I2C_MODE_SACK;
					SDA_low();
					break;
					
				case I2C_MODE_SACK:				//发送标志位结束
					if (SwSlaveI2C.Rw) { 	//主机读从机 从机发送
						if (*(SwSlaveI2C.TxBuf + SwSlaveI2C.TxIdx) & (1 << (7 - SwSlaveI2C.Cnt))) SDA_high();
						else SDA_low();
						SwSlaveI2C.Cnt++;
						SwSlaveI2C.State = I2C_MODE_SEND;
					}
					else { 					//主机写从机 从机接收
						SDA_high();
						SwSlaveI2C.State = I2C_MODE_RECEIVE;
					}
					break;
					
				case I2C_MODE_SEND:				//发送模式
					if (SwSlaveI2C.Cnt < 8) {//一个字节 未 发送完毕
						if (*(SwSlaveI2C.TxBuf + SwSlaveI2C.TxIdx) & (1 << (7 - SwSlaveI2C.Cnt))) SDA_high();
						else SDA_low();
						SwSlaveI2C.Cnt++;
					}
					else {					//一个字节发送完毕
						SwSlaveI2C.Cnt = 0;
						SDA_high();
						SwSlaveI2C.TxIdx++;
						SwSlaveI2C.State = I2C_MODE_RACK;
					}
					break;
					
				case I2C_MODE_RECEIVE:     	//接收8字节完成
					if (SwSlaveI2C.Cnt == 8) {			
						SDA_low();
						SwSlaveI2C.Cnt = 0;
						SwSlaveI2C.State = I2C_MODE_SACK;
						SwSlaveI2C.RxIdx++;
					}
					break;
					
				default:
					break;
				
			}					
		}
	}
	else {												//SDA
		EXTI_ClearITPendingBit(EXTI_Line11);
		
		if (SDA_Read() == Bit_SET) {                    //上升沿
			switch (SwSlaveI2C.State) {
				case I2C_MODE_END:
					if (SCL_Read() == Bit_SET) {
						SwSlaveI2C.State = I2C_MODE_SLEEP;
					}
					break;
				
				case I2C_MODE_RECEIVE:
					if (SCL_Read() == Bit_SET && SwSlaveI2C.Cnt == 1) { // SLEEP
						SwSlaveI2C.State = I2C_MODE_SLEEP;
					}
					break;
					
				default:
					break;
			}
		}                                               
		else {                                          //下降沿
			switch (SwSlaveI2C.State) {					
				case I2C_MODE_SLEEP:				//SLEEP状态下 SDA下降沿，SCL高电平： 起始信号
					if (SCL_Read() == Bit_SET) {
						Address = 0;
						SwSlaveI2C.RxIdx = 0;
						SwSlaveI2C.TxIdx = 0;
						SwSlaveI2C.Cnt = 0;
						SwSlaveI2C.State = I2C_MODE_START;
						SDA_high();
					}
					break;
				
				case I2C_MODE_RECEIVE:
					if (SCL_Read() == Bit_SET && SwSlaveI2C.Cnt == 1) { // RESTART
						Address = 0;
						SwSlaveI2C.RxIdx = 0;
						SwSlaveI2C.TxIdx = 0;
						SwSlaveI2C.Cnt = 0;
						SwSlaveI2C.State = I2C_MODE_START;
						SDA_high();
					}
					break;
					
				default:
//					if (SCL_Read() == Bit_SET) {
//						Address = 0;
//						SwSlaveI2C.RxIdx = 0;
//						SwSlaveI2C.TxIdx = 0;
//						SwSlaveI2C.Cnt = 0;
//						SwSlaveI2C.State = I2C_MODE_START;
//					}
					break;
			}
			
		}                                             
	}                                                 
}
