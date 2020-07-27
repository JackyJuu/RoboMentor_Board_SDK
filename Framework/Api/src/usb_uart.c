#include "usb_uart.h"
#include "string.h"	
#include "stdarg.h"		 
#include "stdio.h"	

#include "usbd_cdc_vcp.h"
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

u8  USART_PRINTF_Buffer[256];	//usb_printf发送缓冲区

void usb_Init(void)
{
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
}

void usb_Receive(uint8_t * pbuf, uint32_t buf_len)
{
		DCD_EP_PrepareRx(&USB_OTG_dev, CDC_OUT_EP, pbuf, buf_len);
}

void usb_SendData(uint8_t data)
{
	VCP_TxData(data);
}

void usb_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_PRINTF_Buffer,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_PRINTF_Buffer);//此次发送数据的长度
	for(j=0;j<i;j++)//循环发送数据
	{
		VCP_TxData(USART_PRINTF_Buffer[j]); 
	}
} 
