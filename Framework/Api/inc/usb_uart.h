#ifndef __USB_USART_H__
#define __USB_USART_H__
#include "stm32f4xx.h"

void usb_Init(void);
void usb_Receive(uint8_t * pbuf, uint32_t buf_len);
void usb_SendData(uint8_t data);
void usb_printf(char* fmt,...);

#endif
