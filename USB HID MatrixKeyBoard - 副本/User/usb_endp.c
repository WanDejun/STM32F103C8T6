// 管理端点回调函数
#include "hw_config.h"
#include "LED.h"

extern __IO uint8_t PrevXferComplete; 
uint8_t Receive_Buffer[2];

/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_OUT_Callback(void) {
	/* Read received data (2 bytes) */  
	USB_SIL_Read(EP1_OUT, Receive_Buffer); 
	
	/*Number Lock*/
	if (Receive_Buffer[0] & 1) {
		LED_Set(GPIO_Pin_0);
	}
	else {
		LED_Reset(GPIO_Pin_0);
	}
	/*Caps Lock*/
	if (Receive_Buffer[0] & 2) {
		LED_Set(GPIO_Pin_1);
	}
	else {
		LED_Reset(GPIO_Pin_1);
	}
	/*Scroll Lock*/
	if (Receive_Buffer[0] & 4) {
		LED_Set(GPIO_Pin_2);
	}
	else {
		LED_Reset(GPIO_Pin_2);
	}
	
	SetEPRxStatus(ENDP1, EP_RX_VALID);
}

/******************************************************************************
* Function Name  : EP1_IN_Callback.
* Description    : EP1 IN Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void) {
	/* Set the transfer complete token to inform upper layer that the current 
	transfer has been complete */
	PrevXferComplete = 1; 
}


/******************************************************************************
* Function Name  : EP2_IN_Callback.
* Description    : EP2 IN Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP2_IN_Callback(void) {
	/* Set the transfer complete token to inform upper layer that the current 
	transfer has been complete */
	;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

