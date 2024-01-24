#include "hw_config.h"

ErrorStatus HSEStartUpStatus;
EXTI_InitTypeDef EXTI_InitStructure;

/* Extern variables ----------------------------------------------------------*/
extern __IO uint8_t PrevXferComplete;

/* Private function prototypes -----------------------------------------------*/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
static void Delay(__IO uint32_t nTime);
/* Private functions ---------------------------------------------------------*/

/**
  * Function Name  : Set_System
  * Description    : Configures Main system clocks & power.
  * Input          : None.
  * Return         : None.
  */
void Set_System(void) {
	GPIO_InitTypeDef  GPIO_InitStructure;  
	/*!< At this stage the microcontroller clock setting is already configured, 
	   this is done through SystemInit() function which is called from startup
	   file (startup_stm32xxx.s) before to branch to application main.
	   To reconfigure the default setting of SystemInit() function, refer to
	   system_stm32xxx.c file
	 */ 

	/******************************************/
	/*           Enable the PWR clock         */
	/******************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
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
void USB_Interrupts_Config(void)
{
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
#if !defined (USE_NUCLEO)
/**
  * Function Name : JoyState.
  * Description   : Decodes the Joystick direction.
  * Input         : None.
  * Output        : None.
  * Return value  : The direction value.
  */
uint8_t JoyState(void)
{
   /* "right" key is pressed */
   if (!STM_EVAL_PBGetState(Button_RIGHT)) {
       return JOY_RIGHT;
   }
   /* "left" key is pressed */
   if (!STM_EVAL_PBGetState(Button_LEFT)) {
       return JOY_LEFT;
   }
   /* "up" key is pressed */
   if (!STM_EVAL_PBGetState(Button_UP)) {
       return JOY_UP;
   }
   /* "down" key is pressed */
   if (!STM_EVAL_PBGetState(Button_DOWN)) {
       return JOY_DOWN;
   }
   /* No key is pressed */
	else {
		return 0;
	} 
}

/**
  * Function Name : Joystick_Send.
  * Description   : prepares buffer to be sent containing Joystick event infos.
  * Input         : Keys: keys received from terminal.
  * Output        : None.
  * Return value  : None.
  */
void Joystick_Send(uint8_t Keys) {
	uint8_t Mouse_Buffer[4] = {0, 0, 0, 0};
	int8_t X = 0, Y = 0;
  
	switch (Keys) {
	case JOY_LEFT:
		X -= CURSOR_STEP;
		break;
	case JOY_RIGHT:
		X += CURSOR_STEP;
		break;
	case JOY_UP:
		Y -= CURSOR_STEP;
		break;
	case JOY_DOWN:
		Y += CURSOR_STEP;
		break;
	default:
		return;
	}
	/* prepare buffer to send */
	Mouse_Buffer[1] = X;
	Mouse_Buffer[2] = Y;

	/* Reset the control token to inform upper layer that a transfer is ongoing */
	PrevXferComplete = 0;

	/* Copy mouse position info in ENDP1 Tx Packet Memory Area*/
	USB_SIL_Write(EP1_IN, Mouse_Buffer, 4);

	/* Enable endpoint for transmission */
	SetEPTxValid(ENDP1);
}
#endif /* USE_NUCLEO */
/**
  * Function Name  : Joy_Emul.
  * Description    : Gets Pointer Data
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void Joy_Emul(void)
{
  uint8_t Mouse_Buffer[4] = {0, 0, 0, 0};
  uint8_t X = 0, Y = 0; 
  static uint8_t Sens = 0;
  static uint8_t Step = 0;
  
  Delay(0x0FFFF);
  
  if (Step == 35)
  {
    Step = 0;
    Sens++;
  }
  
  if(Sens == 0)
  {
    X = Step++;
    Y = 0;
  }
  
  if(Sens == 1)
  {
    Y = Step++;
    X = 0;
  }      
  if (Sens==2)
  {
    X = 256 - Step++;
    Y = 0;
  } 
  
  if (Sens == 3)
  {
    Y = 256 - Step++;
    X = 0;
  }
  
  if (Sens == 4)
  { 
    Sens = 0;
    X = 0;
    Y = 0;
  }
  
  Mouse_Buffer[0] = 0;
  Mouse_Buffer[1] = X;
  Mouse_Buffer[2] = Y;
  Mouse_Buffer[3] = 0;
  
  /* Reset the control token to inform upper layer that a transfer is ongoing */
  PrevXferComplete = 0;
  /* Copy mouse position info in ENDP1 Tx Packet Memory Area*/
  USB_SIL_Write(EP1_IN, Mouse_Buffer, 4);
  /* Enable endpoint for transmission */
  SetEPTxValid(ENDP1);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
static void Delay(__IO uint32_t nTime)
{
  for(; nTime != 0; nTime--);
}

/**
  * Function Name  : Get_SerialNum.
  * Description    : Create the serial number string descriptor.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void Get_SerialNum(void)
{
	uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

	Device_Serial0 = *(uint32_t*)ID1;
	Device_Serial1 = *(uint32_t*)ID2;
	Device_Serial2 = *(uint32_t*)ID3;

	Device_Serial0 += Device_Serial2;

	if (Device_Serial0 != 0) {
		IntToUnicode (Device_Serial0, &Joystick_StringSerial[2] , 8);
		IntToUnicode (Device_Serial1, &Joystick_StringSerial[18], 4);
	}
}

/**
  * Function Name  : HexToChar.
  * Description    : Convert Hex 32Bits value into char.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
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
    
    pbuf[ 2* idx + 1] = 0;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
