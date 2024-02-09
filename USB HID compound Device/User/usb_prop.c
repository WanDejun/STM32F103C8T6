#include "usb_prop.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ProtocolValue;

/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table = {
    EP_NUM,
    1
};

DEVICE_PROP Device_Property = {
    KeyBoard_init,
    KeyBoard_Reset,
    KeyBoard_Status_In,
    KeyBoard_Status_Out,
    KeyBoard_Data_Setup,
    KeyBoard_NoData_Setup,
    KeyBoard_Get_Interface_Setting,
    KeyBoard_GetDeviceDescriptor,
    KeyBoard_GetConfigDescriptor,
    KeyBoard_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
 };

USER_STANDARD_REQUESTS User_Standard_Requests = {
    KeyBoard_GetConfiguration,
    KeyBoard_SetConfiguration,
    KeyBoard_GetInterface,
    KeyBoard_SetInterface,
    KeyBoard_GetStatus,
    KeyBoard_ClearFeature,
    KeyBoard_SetEndPointFeature,
    KeyBoard_SetDeviceFeature,
    KeyBoard_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor = {
    (uint8_t*)KeyBoard_DeviceDescriptor,
    KEYBOARD_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor = {
    (uint8_t*)KeyBoard_ConfigDescriptor,
    KEYBOARD_CONFIG_DESC
};

ONE_DESCRIPTOR KeyBoard_Report_Descriptor = {
    (uint8_t *)KeyBoard_ReportDescriptor,
    KEYBOARD_REPORT_DESC
};

ONE_DESCRIPTOR Audio_Equipment_Controller_Report_Descriptor = {
    (uint8_t *)Audio_Equipment_Controller_ReportDescriptor,
    AUDIO_EQUIPMENT_CONTROLLER_REPORT_DESC
};

ONE_DESCRIPTOR KeyBoard_Hid_Descriptor = {
    (uint8_t*)KeyBoard_ConfigDescriptor + KEYBOARD_OFF_HID_DESC,
    KEYBOARD_HID_DESC
};

ONE_DESCRIPTOR Audio_Equipment_Controller_Hid_Descriptor = {
    (uint8_t*)KeyBoard_ConfigDescriptor + AUDIO_EQUIPMENT_CONTROLLER_OFF_HID_DESC,
    KEYBOARD_HID_DESC
};

ONE_DESCRIPTOR String_Descriptor[4] = {
    {(uint8_t*)KeyBoard_StringLangID, KEYBOARD_STRING_LANGID},
    {(uint8_t*)KeyBoard_StringVendor, KEYBOARD_STRING_VENDOR},
    {(uint8_t*)KeyBoard_StringProduct, KEYBOARD_STRING_PRODUCT},
    {(uint8_t*)KeyBoard_StringSerial, KEYBOARD_STRING_SERIAL}
};

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * Function Name  : KeyBoard_init.
  * Description    : KeyBoard Mouse init routine.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void KeyBoard_init(void) {
	/* Update the serial number string descriptor with the data from the unique
	ID*/
	Get_SerialNum();

	pInformation->Current_Configuration = 0;
	/* Connect the device */
	PowerOn();

	/* Perform basic device initialization operations */
	USB_SIL_Init();

	bDeviceState = UNCONNECTED;
}

/**
  * Function Name  : KeyBoard_Reset.
  * Description    : KeyBoard Mouse reset routine.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void KeyBoard_Reset(void) {
	/* Set KeyBoard_DEVICE as not configured */
	pInformation->Current_Configuration = 0;
	pInformation->Current_Interface = 0;/*the default Interface*/

	/* Current Feature initialization */
	pInformation->Current_Feature = KeyBoard_ConfigDescriptor[7];
	SetBTABLE(BTABLE_ADDRESS);
	
	/* Initialize Endpoint 0 */
	SetEPType(ENDP0, EP_CONTROL);
	SetEPTxStatus(ENDP0, EP_TX_STALL);
	SetEPRxAddr(ENDP0, ENDP0_RXADDR);
	SetEPTxAddr(ENDP0, ENDP0_TXADDR);
	Clear_Status_Out(ENDP0);
	SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
	SetEPRxValid(ENDP0);

	/* Initialize Endpoint 1 */
	SetEPType(ENDP1, EP_INTERRUPT);
	SetEPTxAddr(ENDP1, ENDP1_TXADDR);
	SetEPRxAddr(ENDP1, ENDP1_RXADDR);
	SetEPTxCount(ENDP1, 15);
	SetEPRxCount(ENDP1, 2);
	SetEPRxStatus(ENDP1, EP_RX_VALID);
	SetEPTxStatus(ENDP1, EP_TX_NAK);

	SetEPType(ENDP2, EP_INTERRUPT);
	SetEPTxAddr(ENDP2, ENDP2_TXADDR);
	SetEPTxCount(ENDP2, 2);
	SetEPTxStatus(ENDP2, EP_TX_NAK);
	
	/* Set this device to response on default address */
	SetDeviceAddress(0);
	bDeviceState = ATTACHED;
}

/**
  * Function Name  : KeyBoard_SetConfiguration.
  * Description    : Update the device state to configured.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void KeyBoard_SetConfiguration(void) {
	DEVICE_INFO *pInfo = &Device_Info;

	if (pInfo->Current_Configuration != 0) {
		/* Device configured */
		bDeviceState = CONFIGURED;
	}
}

/**
  * Function Name  : KeyBoard_SetConfiguration.
  * Description    : Update the device state to addressed.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void KeyBoard_SetDeviceAddress (void) {
  bDeviceState = ADDRESSED;
}
/**
  * Function Name  : KeyBoard_Status_In.
  * Description    : KeyBoard status IN routine.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void KeyBoard_Status_In(void) {

}

/**
  * Function Name  : KeyBoard_Status_Out
  * Description    : KeyBoard status OUT routine.
  * Input          : None.
  * Output         : None.
  * Return         : None.
  */
void KeyBoard_Status_Out (void) {

}

/**
  * Function Name  : KeyBoard_Data_Setup
  * Description    : Handle the data class specific requests.
  * Input          : Request Nb.
  * Output         : None.
  * Return         : USB_UNSUPPORT or USB_SUCCESS.
  */
RESULT KeyBoard_Data_Setup(uint8_t RequestNo) {
	uint8_t *(*CopyRoutine)(uint16_t);

	CopyRoutine = NULL;
	if ((RequestNo == GET_DESCRIPTOR) 
		&& (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT)) 
		&& (pInformation->USBwIndex0 <= 1)) {
		if (pInformation->USBwValue1 == REPORT_DESCRIPTOR) {
			if (pInformation->USBwIndex0 == 0) CopyRoutine = KeyBoard_GetReportDescriptor;
			else if (pInformation->USBwIndex0 == 1) CopyRoutine = Audio_Equipment_Controller_GetReportDescriptor;
		}
		else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE) {
			if (pInformation->USBwIndex0 == 0) CopyRoutine = KeyBoard_GetHIDDescriptor;
			else if (pInformation->USBwIndex0 == 1) CopyRoutine = Audio_Equipment_Controller_GetHIDDescriptor;
		}

	} /* End of GET_DESCRIPTOR */

	/*** GET_PROTOCOL ***/
	else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) && RequestNo == GET_PROTOCOL) {
		CopyRoutine = KeyBoard_GetProtocolValue;
	}
	if (CopyRoutine == NULL) {
		return USB_UNSUPPORT;
	}
	pInformation->Ctrl_Info.CopyData = CopyRoutine;
	pInformation->Ctrl_Info.Usb_wOffset = 0;
	(*CopyRoutine)(0);
	return USB_SUCCESS;
}

/**
  * Function Name  : KeyBoard_NoData_Setup
  * Description    : handle the no data class specific requests
  * Input          : Request Nb.
  * Output         : None.
  * Return         : USB_UNSUPPORT or USB_SUCCESS.
  */
RESULT KeyBoard_NoData_Setup(uint8_t RequestNo) {
	if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
		&& (RequestNo == SET_PROTOCOL)) {
		return KeyBoard_SetProtocol();
	}
	else {
		return USB_UNSUPPORT;
	}
}

/**
  * Function Name  : KeyBoard_GetDeviceDescriptor.
  * Description    : Gets the device descriptor.
  * Input          : Length
  * Output         : None.
  * Return         : The address of the device descriptor.
  */
uint8_t *KeyBoard_GetDeviceDescriptor(uint16_t Length) {
	return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/**
  * Function Name  : KeyBoard_GetConfigDescriptor.
  * Description    : Gets the configuration descriptor.
  * Input          : Length
  * Output         : None.
  * Return         : The address of the configuration descriptor.
  */
uint8_t *KeyBoard_GetConfigDescriptor(uint16_t Length) {
	return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/**
  * Function Name  : KeyBoard_GetStringDescriptor
  * Description    : Gets the string descriptors according to the needed index
  * Input          : Length
  * Output         : None.
  * Return         : The address of the string descriptors.
  */
uint8_t *KeyBoard_GetStringDescriptor(uint16_t Length) {
	uint8_t wValue0 = pInformation->USBwValue0;
	if (wValue0 >= 4) {
		return NULL;
	}
	else {
		return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
	}
}

/**
  * Function Name  : KeyBoard_GetReportDescriptor.
  * Description    : Gets the HID report descriptor.
  * Input          : Length
  * Output         : None.
  * Return         : The address of the configuration descriptor.
  */
uint8_t *KeyBoard_GetReportDescriptor(uint16_t Length) {
	return Standard_GetDescriptorData(Length, &KeyBoard_Report_Descriptor);
}

/**
  * Function Name  : Audio_Equipment_Controller_GetReportDescriptor.
  * Description    : Gets the HID report descriptor.
  * Input          : Length
  * Output         : None.
  * Return         : The address of the configuration descriptor.
  */
uint8_t *Audio_Equipment_Controller_GetReportDescriptor(uint16_t Length) {
	return Standard_GetDescriptorData(Length, &Audio_Equipment_Controller_Report_Descriptor);
}

/**
  * Function Name  : KeyBoard_GetHIDDescriptor.
  * Description    : Gets the HID descriptor.
  * Input          : Length
  * Output         : None.
  * Return         : The address of the configuration descriptor.
  */
uint8_t *KeyBoard_GetHIDDescriptor(uint16_t Length) {
	return Standard_GetDescriptorData(Length, &KeyBoard_Hid_Descriptor);
}

/**
  * Function Name  : Audio_Equipment_Controller_GetHIDDescriptor.
  * Description    : Gets the HID descriptor.
  * Input          : Length
  * Output         : None.
  * Return         : The address of the configuration descriptor.
  */
uint8_t *Audio_Equipment_Controller_GetHIDDescriptor(uint16_t Length) {
	return Standard_GetDescriptorData(Length, &Audio_Equipment_Controller_Hid_Descriptor);
}

/**
  * Function Name  : KeyBoard_Get_Interface_Setting.
  * Description    : tests the interface and the alternate setting according to the
  *                  supported one.
  * Input          : - Interface : interface number.
  *                  - AlternateSetting : Alternate Setting number.
  * Output         : None.
  * Return         : USB_SUCCESS or USB_UNSUPPORT.
  */
RESULT KeyBoard_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting) {
	if (AlternateSetting > 0) {
		return USB_UNSUPPORT;
	}
	else if (Interface > 0) {
		return USB_UNSUPPORT;
	}
	return USB_SUCCESS;
}

/**
  * Function Name  : KeyBoard_SetProtocol
  * Description    : KeyBoard Set Protocol request routine.
  * Input          : None.
  * Output         : None.
  * Return         : USB SUCCESS.
  */
RESULT KeyBoard_SetProtocol(void) {
	uint8_t wValue0 = pInformation->USBwValue0;
	ProtocolValue = wValue0;
	return USB_SUCCESS;
}

/**
  * Function Name  : KeyBoard_GetProtocolValue
  * Description    : get the protocol value
  * Input          : Length.
  * Output         : None.
  * Return         : address of the protocol value.
  */
uint8_t *KeyBoard_GetProtocolValue(uint16_t Length) {
	if (Length == 0) {
		pInformation->Ctrl_Info.Usb_wLength = 1;
		return NULL;
	}
	else {
		return (uint8_t *)(&ProtocolValue);
	}
}
