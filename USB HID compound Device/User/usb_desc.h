#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05
#define HID_DESCRIPTOR_TYPE                     0x21

#define KEYBOARD_HID_DESC                   	0x09
#define KEYBOARD_OFF_HID_DESC                   0x12
#define AUDIO_EQUIPMENT_CONTROLLER_OFF_HID_DESC 0x32

#define KEYBOARD_DEVICE_DESC                	18
#define KEYBOARD_CONFIG_DESC                	66
#define KEYBOARD_REPORT_DESC                	73
#define AUDIO_EQUIPMENT_CONTROLLER_REPORT_DESC 	51

#define KEYBOARD_STRING_LANGID              	4
#define KEYBOARD_STRING_VENDOR              	38
#define KEYBOARD_STRING_PRODUCT             	30
#define KEYBOARD_STRING_SERIAL              	26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* Exported functions ------------------------------------------------------- */
extern const uint8_t KeyBoard_DeviceDescriptor[KEYBOARD_DEVICE_DESC];
extern const uint8_t KeyBoard_ConfigDescriptor[KEYBOARD_CONFIG_DESC];
extern const uint8_t KeyBoard_ReportDescriptor[KEYBOARD_REPORT_DESC];
extern const uint8_t Audio_Equipment_Controller_ReportDescriptor[AUDIO_EQUIPMENT_CONTROLLER_REPORT_DESC];

extern const uint8_t KeyBoard_StringLangID[KEYBOARD_STRING_LANGID];
extern const uint8_t KeyBoard_StringVendor[KEYBOARD_STRING_VENDOR];
extern const uint8_t KeyBoard_StringProduct[KEYBOARD_STRING_PRODUCT];
extern uint8_t KeyBoard_StringSerial[KEYBOARD_STRING_SERIAL];

#endif /* __USB_DESC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
