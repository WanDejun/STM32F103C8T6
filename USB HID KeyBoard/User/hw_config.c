#include "hw_config.h"

ErrorStatus HSEStartUpStatus;
EXTI_InitTypeDef EXTI_InitStructure;

/* Extern variables ----------------------------------------------------------*/
extern __IO uint8_t PrevXferComplete;

/* Private function prototypes -----------------------------------------------*/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
/* Private functions ---------------------------------------------------------*/

static __IO uint8_t KeyBoard_Buffer[15] = {};

/**
  * Function Name  : Set_System
  * Description    : Configures Main system clocks & power.
  * Input          : None.
  * Return         : None.
  */
void Set_System(void) {
	GPIO_InitTypeDef  GPIO_InitStructure;  
	/******************************************/
	/*           Enable the PWR clock         */
	/******************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 初始化按键(全在GPIOA口), 有需要可以更改
	uint8_t i;
	uint16_t GPIO_Pin_AllKey = 0;
	extern const uint16_t KEY_PIN[KEYn];
	
	for (i = 0; i < KEYn; i++) {
		GPIO_Pin_AllKey |= KEY_PIN[i];
	}
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_AllKey;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
} 
 
/**
  * Function Name  : Set_USBClock
  * Description    : Configures USB Clock input (48MHz).
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void Set_USBClock(void) {
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  
  /* Enable the USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/**
  * Function Name  : Leave_LowPowerMode.
  * Description    : Restores system clocks and power while exiting suspend mode.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;
  
  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0) {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else {
    bDeviceState = ATTACHED;
  }
}

/**
  * Function Name  : USB_Interrupts_Config.
  * Description    : Configures the USB interrupts.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void USB_Interrupts_Config(void) {
  NVIC_InitTypeDef NVIC_InitStructure;

  /* 2 bit for pre-emption priority, 2 bits for subpriority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * Function Name  : USB_Cable_Config.
  * Description    : Software Connection/Disconnection of USB Cable.
  * Input          : NewState: new state.
  * Output         : None.
  * Return         : None
  */
void USB_Cable_Config (FunctionalState NewState) { 
	if (NewState != DISABLE) {
		GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
	}
	else {
		GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
	}
}

/**
  * Function Name : KeyState
  * Description   : 更新按键信息，具体缓冲区与按键的对应关系参考报告描述符和HID Usage Table(P89)，按键更新可以进一步封装
  * Input         : None.
  * Output        : None.
  * Return value  : The direction value.
  */
uint8_t KeyState(void) {
	uint8_t state = 0;
	
	/* "ALL" key is updated */
	if (!GetKeyState(KEY_ALL)) {
		if (!(KeyBoard_Buffer[2] & 16)) {
			KeyBoard_Buffer[2] |= 0xF0;
			KeyBoard_Buffer[3] = KeyBoard_Buffer[4] = 0xFF;
			KeyBoard_Buffer[5] = 0x03;
			state |= 1;
		}
	}
	else {
		if (KeyBoard_Buffer[2] & 16) {
			KeyBoard_Buffer[2] &= (~0xF0);
			KeyBoard_Buffer[3] = KeyBoard_Buffer[4] = 0x00;
			KeyBoard_Buffer[5] = 0x00;
			state |= 1;
		}
	}
	
	/**	
	* @brief Key event
	**/
	/* "A" key is updated*/
	if (!GetKeyState(KEY_a_A)) { 
		KeyBoard_Buffer[2] |= 1;
		state |= 1;
	}
	else {
		KeyBoard_Buffer[2] &= (~1);
		state |= 1;
	}
	/* "B" key is updated */
	if (!GetKeyState(KEY_b_B)) {
		if (!(KeyBoard_Buffer[2] & 2)) {
			KeyBoard_Buffer[2] |= 2;
			state |= 1;
		}
	}
	else {
		if (KeyBoard_Buffer[2] & 2) {
			KeyBoard_Buffer[2] &= (~2);
			state |= 1;
		}
	}
	/* "C" key is updated */
	if (!GetKeyState(KEY_c_C)) {
		if (!(KeyBoard_Buffer[2] & 4)) {
			KeyBoard_Buffer[2] |= 4;
			state |= 1;
		}
	}
	else {
		if (KeyBoard_Buffer[2] & 4) {
			KeyBoard_Buffer[2] &= (~4);
			state |= 1;
		}
	}
	/* "D" key is updated */
	if (!GetKeyState(KEY_d_D)) {
		if (!(KeyBoard_Buffer[2] & 8)) {
			KeyBoard_Buffer[2] |= 8;
			state |= 1;
		}
	}
	else {
		if (KeyBoard_Buffer[2] & 8) {
			KeyBoard_Buffer[2] &= (~8);
			state |= 1;
		}
	}
	
	return state;
}

/**
  * Function Name : KeyBoard_Send.
  * Description   : prepares buffer to be sent containing KeyBoard event infos.
  * Input         : Keys: keys received from terminal.
  * Output        : None.
  * Return value  : None.
  */
void KeyBoard_Send() {
	/* Reset the control token to inform upper layer that a transfer is ongoing */
	PrevXferComplete = 0;

	/* Copy mouse position info in ENDP1 Tx Packet Memory Area*/
	USB_SIL_Write(EP1_IN, (uint8_t*)KeyBoard_Buffer, 15);

	/* Enable endpoint for transmission */
	SetEPTxValid(ENDP1);
}

/**
  * Function Name  : Get_SerialNum.
  * Description    : Create the serial number string descriptor.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void Get_SerialNum(void) {
	uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

	Device_Serial0 = *(uint32_t*)ID1;
	Device_Serial1 = *(uint32_t*)ID2;
	Device_Serial2 = *(uint32_t*)ID3;

	Device_Serial0 += Device_Serial2;

	if (Device_Serial0 != 0) {
		IntToUnicode (Device_Serial0, &KeyBoard_StringSerial[2] , 8);
		IntToUnicode (Device_Serial1, &KeyBoard_StringSerial[18], 4);
	}
}

/**
  * Function Name  : HexToChar.
  * Description    : Convert Hex 32Bits value into char.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len) {
  uint8_t idx = 0;
  
  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2* idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2* idx] = (value >> 28) + 'A' - 10; 
    }
    
    value = value << 4;
    
    pbuf[2* idx + 1] = 0;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
