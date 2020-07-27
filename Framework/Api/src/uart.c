#include "stm32f4xx.h"
#include "uart.h"
#include "delay.h"
#include <stdio.h>
#include <stdarg.h>
#include "usart_steering.h"
#include "usbd_cdc_vcp.h"
#include "usb_uart.h"

#include "Cjson_Task.h"

extern Steering_Read_Mode_t Steering_Read_Mode;

extern Uart_Mode_t Uart_Mode;

extern __ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

extern uint8_t data_last[];

uint8_t Steering_Usart_Buff[64];
uint8_t Steering_Usart_Lenth;
uint8_t Steering_Usart_Sum;
uint8_t Steering_Usart_Data[64];
int Steering_Uart_Finish;

uint8_t USART2_RX_BUF[1024];
uint8_t USART3_RX_BUF[1024];
uint8_t USART6_RX_BUF[1024];
uint8_t UART7_RX_BUF[1024];
uint8_t UART8_RX_BUF[1024];

int USART1_RX_LEN;
int USART2_RX_LEN;
int USART3_RX_LEN;
int USART6_RX_LEN;
int UART7_RX_LEN;
int UART8_RX_LEN;

int RX_LENTH;
int RX_FLAG;

static void Uart_Process(uint8_t data,USART_t USART);
static void Steering_Uart(uint8_t data,USART_t USART);

uint8_t rx[1024];




/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void USART1_Init(void)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	  /* Enable the USART OverSampling by 8 */
  USART_OverSampling8Cmd(USART1, ENABLE); 
	
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(USART1, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
  USART1_printf(" USART1 Printf Example: retarget the C library printf function to the USART1.\r\n");
 
}





/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void USART2_Init(void)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_DeInit(USART2);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(USART2, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 USART2_printf(" USART2 Printf Example: retarget the C library printf function to the USART2.\r\n");
}

/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void USART3_Init(void)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_DeInit(USART3);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(USART3, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 USART3_printf(" USART3 Printf Example: retarget the C library printf function to the USART3.\r\n");
}




/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void USART6_Init(void)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	USART_DeInit(USART6);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART6, &USART_InitStructure);
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(USART6, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 USART6_printf(" USART6 Printf Example: retarget the C library printf function to the USART6.\r\n");
}



/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void UART7_Init(void)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_UART7);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_UART7); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	USART_DeInit(UART7);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(UART7, &USART_InitStructure);
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(UART7, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 UART7_printf(" UART7 Printf Example: retarget the C library printf function to the USART7.\r\n");
}


/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void UART8_Init(void)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_UART8);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_UART8); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	USART_DeInit(UART8);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(UART8, &USART_InitStructure);
	USART_ITConfig(UART8, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(UART8, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 UART8_printf(" UART8 Printf Example: retarget the C library printf function to the UART8.\r\n");
}



/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void USART1_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	  /* Enable the USART OverSampling by 8 */
  USART_OverSampling8Cmd(USART1, ENABLE); 
	
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = Usart_Parity;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = Usart_Mode;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(USART1, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
  USART1_printf(" USART1 Printf Example: retarget the C library printf function to the USART1.\r\n");
 
}





/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void USART2_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_DeInit(USART2);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = Usart_Parity;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = Usart_Mode;

  USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(USART2, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 USART2_printf(" USART2 Printf Example: retarget the C library printf function to the USART2.\r\n");
}

/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void USART3_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_DeInit(USART3);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = Usart_Parity;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = Usart_Mode;

  USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(USART3, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 USART3_printf(" USART3 Printf Example: retarget the C library printf function to the USART3.\r\n");
}




/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void USART6_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	USART_DeInit(USART6);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = Usart_Parity;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = Usart_Mode;

  USART_Init(USART6, &USART_InitStructure);
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(USART6, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 USART6_printf(" USART6 Printf Example: retarget the C library printf function to the USART6.\r\n");
}



/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void UART7_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_UART7);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_UART7); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	USART_DeInit(UART7);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = Usart_Parity;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = Usart_Mode;

  USART_Init(UART7, &USART_InitStructure);
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(UART7, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 UART7_printf(" UART7 Printf Example: retarget the C library printf function to the USART7.\r\n");
}


/**
  * @brief  Configures the USART1 Peripheral.
  * @param  None
  * @retval None
  */
void UART8_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_UART8);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_UART8); 
	
	/* Configure USART1 as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	USART_DeInit(UART8);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = Usart_Parity;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = Usart_Mode;

  USART_Init(UART8, &USART_InitStructure);
	USART_ITConfig(UART8, USART_IT_RXNE, ENABLE);        //usart rx idle interrupt  enabled
	
	/* Enable USART */
  USART_Cmd(UART8, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
 
 UART8_printf(" UART8 Printf Example: retarget the C library printf function to the UART8.\r\n");
}










#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

uint8_t USART1_RX[1024];
uint8_t USART2_RX[1024];
uint8_t USART3_RX[1024];
uint8_t USART6_RX[1024];
uint8_t UART7_RX[1024];
uint8_t UART8_RX[1024];

void RoboMentor_uart_process(uint8_t data,USART_t USART)
{
	if(Uart_Mode == Steering_Uart_Mode)
		Steering_Uart(data,USART);
	else
		Uart_Process(data,USART);
	
}

static void Steering_Message_Get(uint8_t* Msg,Steering_Read_Mode_t Steering_Read_Mode)
{
	int steering_ID_get;
	steering_ID_get = Msg[2];
			switch(Steering_Read_Mode)
			{
				case STEERING_READ_MODE://读取总线舵机模式
				{
					int steering_mode_get,steering_speed;
					steering_mode_get = Msg[5];
					steering_speed = BYTE_TO_HW(Msg[8],Msg[7]);
					if(steering_speed > 35512)
						steering_speed = steering_speed - 65536;	

					usb_printf("{\"type\":\"SERVO-READ-MODE\",\"id\":%d,\"mode\":%d,\"speed\":%d}",steering_ID_get,steering_mode_get,steering_speed);
//					usb_printf();("steering_mode_get = %d , steering_speed = %d  	\r\n",steering_mode_get,steering_speed);
					break;
				}
				case STEERING_READ_ID://读取总线舵机ID
				{
					int steering_ID;
					steering_ID = Msg[5];
					usb_printf("{\"type\":\"SERVO-READ-ID\",\"id\":%d}",steering_ID);
//					usb_printf("steering_ID = %d  	\r\n",steering_ID);
					break;
				}
				case STEERING_ANGLE_OFFSET_READ://读取总线舵机偏差值
				{
					int steering_offset_angle;
					steering_offset_angle = Msg[5];
					if(steering_offset_angle >= 130)
						steering_offset_angle = steering_offset_angle - 256;
						usb_printf("{\"type\":\"SERVO-ANGLE-OFFSET-READ\",\"id\":%d,\"value\":%d}",steering_ID_get,steering_offset_angle);
//					usb_printf("steering_offset_angle = %d  	\r\n",steering_offset_angle);
					break;
				}
				case STEERING_ANGLE_LIMIT_READ://读取总线舵机角度范围
				{
					int steering_min_angle,steering_max_angle;
					steering_min_angle = BYTE_TO_HW(Msg[6],Msg[5]);
					steering_max_angle = BYTE_TO_HW(Msg[8],Msg[7]);			
					usb_printf("{\"type\":\"SERVO-ANGLE-LIMIT-READ\",\"id\":%d,\"min\":%d,\"max\":%d}",steering_ID_get,steering_min_angle,steering_max_angle);
//					usb_printf("steering_min_angle = %d , steering_max_angle = %d  	\r\n",steering_min_angle,steering_max_angle);
					break;
				}
				case STEERING_VIN_LIMIT_READ://读取总线舵机电压范围
				{
					int steering_min_vin,steering_max_vin;
					steering_min_vin = BYTE_TO_HW(Msg[6],Msg[5]);
					steering_max_vin = BYTE_TO_HW(Msg[8],Msg[7]);			
					usb_printf("{\"type\":\"SERVO-VIN-LIMIT-READ\",\"id\":%d,\"min\":%d,\"max\":%d}",steering_ID_get,steering_min_vin,steering_max_vin);					
//					usb_printf("steering_min_vin = %d , steering_max_angle = %d  	\r\n",steering_min_vin,steering_max_vin);
					break;
				}
				case STEERING_MOTION_READ://总线舵机运动状态读取
				{
					int steering_motion_angle,steering_motion_time;
					steering_motion_angle = BYTE_TO_HW(Msg[6],Msg[5]);
					steering_motion_time = BYTE_TO_HW(Msg[8],Msg[7]);	
					usb_printf("{\"type\":\"SERVO-MOTION-READ\",\"id\":%d,\"angle\":%d,\"time\":%d}",steering_ID_get,steering_motion_angle,steering_motion_time);					
//				usb_printf("steering_motion_angle = %d , steering_motion_time = %d  	\r\n",steering_motion_angle,steering_motion_time);
					break;
				}
				case STEERING_VIN_READ://读取总线舵机当前输入电压
				{
					int steering_vin;
					steering_vin = BYTE_TO_HW(Msg[6],Msg[5]);
					usb_printf("{\"type\":\"SERVO-VIN-READ\",\"id\":%d,\"vin\":%d}",steering_ID_get,steering_vin);
					//					usb_printf("steering_vin = %d  	\r\n",steering_vin);
					break;
				}
				case STEERING_POS_READ://读取总线舵机当前位置角度数据
				{
					signed short int steering_now_angle;
					steering_now_angle = (signed short int)BYTE_TO_HW(Msg[6],Msg[5]);	
					usb_printf("{\"type\":\"SERVO-POS-READ\",\"id\":%d,\"pos\":%d}",steering_ID_get,steering_now_angle);					
//					usb_printf("steering_now_angle = %d   \r\n",steering_now_angle);
					break;
				}
				case STEERING_STATUS_READ://读取总线舵机当前位置角度数据
				{
					signed short int steering_now_status;
					steering_now_status = Msg[5];	
					usb_printf("{\"type\":\"SERVO-STATUS-READ\",\"id\":%d,\"status\":%d}",steering_ID_get,steering_now_status);					
//					usb_printf("steering_now_angle = %d   \r\n",steering_now_angle);
					break;
				}
			}
				
}


static void Steering_Uart(uint8_t data,USART_t USART)
{
		uint8_t last_Data,i;
			if((data == 0x55)&&(last_Data == 0x55))
			{
				Steering_Usart_Lenth = 2;
				Steering_Usart_Buff[0] = 0x55;
				Steering_Usart_Buff[1] = 0x55;
			}
			else if((data == LobotCheckSum(Steering_Usart_Buff)) && (Steering_Usart_Lenth > 4))
			{   
				
				for(i = 0;i<32;i++)
				{
					Steering_Usart_Data[i] = 0;
				}
				
				for(i = 0;i<Steering_Usart_Buff[3]+3;i++)
				{
					Steering_Usart_Data[i] = Steering_Usart_Buff[i];
				}
				
				Steering_Message_Get(Steering_Usart_Data,Steering_Read_Mode);
				
				
				for(i = 0;i<32;i++)
				{
					Steering_Usart_Buff[i] = 0;
				}
				
				Steering_Usart_Lenth = 0;
				Uart_Mode = Normel_Uart_Mode;	
			}
			else
			{
				Steering_Usart_Buff[Steering_Usart_Lenth] = data;
				Steering_Usart_Lenth++;
			}
			last_Data = data;
}


static void Uart_Process(uint8_t data,USART_t USART)
{
		static uint8_t USART_RX_BUF[1024];
		static int n=0;
		static uint8_t lastdata;	
			if((lastdata == data_last[0])&&(data == data_last[1]))
			{
				switch(USART)
				{
					case USART_1:
					{
						for(int i = 0;i < n-1;i++)
						{
							USART1_RX[i] = USART_RX_BUF[i];
							if(i == n-2)
								RX_FLAG = 1;
						}
						break;
					}
					case USART_2:
					{
						for(int i = 0;i < n-1;i++)
						{
							USART2_RX[i] = USART_RX_BUF[i];
							if(i == n-2)
								RX_FLAG = 1;
						}
						break;
					}
					case USART_3:
					{
						for(int i = 0;i < n-1;i++)
						{
							USART3_RX[i] = USART_RX_BUF[i];
							if(i == n-2)
								RX_FLAG = 1;
						}
						break;
					}
					case USART_6:
					{
						for(int i = 0;i < n-1;i++)
						{
							USART6_RX[i] = USART_RX_BUF[i];
							if(i == n-2)
								RX_FLAG = 1;
						}
						break;
					}
					case UART_7:
					{
						for(int i = 0;i < n-1;i++)
						{
							UART7_RX[i] = USART_RX_BUF[i];
							if(i == n-2)
								RX_FLAG = 1;
						}
						break;
					}
					case UART_8:
					{
						for(int i = 0;i < n-1;i++)
						{
							UART8_RX[i] = USART_RX_BUF[i];
							if(i == n-2)
								RX_FLAG = 1;
						}
						break;
					}
				
			}
				n=0;
			}
			else
			{
				USART_RX_BUF[n++] = data;
			}
			
			if(n > 1022)
			{
				n = 0;
			}
			lastdata = data;
}


void UART_DATA_RX_TEST(int lenth,uint8_t data,uint8_t *UART_RX)
{
		static uint8_t USART_RX_BUF[1024];
		static int n=0;
			if(n == lenth)
			{
				if(RX_FLAG == 1)
					for(int i = 0;i < lenth;i++)
					{
						UART_RX[i] = USART_RX_BUF[i];
						if(i == lenth-1)
							RX_FLAG = 2;
					}
				n=0;
			}
			else
			{
				USART_RX_BUF[n++] = data;
			}
}


//void USART1_IRQHandler(void)                
//{
//	static uint8_t data;
//  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
//    {
//			data = USART_ReceiveData(USART1);
//			RoboMentor_uart_process(data,USART1_RX);
//		}				
//}


////void USART1_IRQHandler(void)                
////{
////	static int n=0;
////	static uint8_t data,lastdata;
////  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
////    {
////			USART_ClearFlag(USART1, USART_FLAG_RXNE);
////			data = USART_ReceiveData(USART1);
////			if((lastdata == '\\')&&(data == 'n'))
////			{
////				for(int i = 0;i < n-1;i++)
////				{
////				USART1_RX[i] = USART1_RX_BUF[i];
////				}
////				n=0;
////			}
////			else
////			{
////				USART1_RX_BUF[n++] = data;
////			}
////			lastdata = data;
////		}				
////}

//void USART2_IRQHandler(void)                
//{
//	static int n=0;
//	static uint8_t data,lastdata;
//  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
//    {
//			USART_ClearFlag(USART2, USART_FLAG_RXNE);
//			data = USART_ReceiveData(USART2);
//			if((lastdata == '\\')&&(data == 'n'))
//			{
//				for(int i = 0;i < n-1;i++)
//				{
//				USART2_RX[i] = USART2_RX_BUF[i];
//				}
//				n=0;
//			}
//			else
//			{
//				USART2_RX_BUF[n++] = data;
//			}
//			lastdata = data;
//		}				
//}

//void USART3_IRQHandler(void)                
//{
//	static int n=0;
//	static uint8_t data,lastdata;
//  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
//    {
//			USART_ClearFlag(USART3, USART_FLAG_RXNE);
//			data = USART_ReceiveData(USART3);
//			if((lastdata == '\\')&&(data == 'n'))
//			{
//				for(int i = 0;i < n-1;i++)
//				{
//				USART3_RX[i] = USART3_RX_BUF[i];
//				}
//				n=0;
//			}
//			else
//			{
//				USART3_RX_BUF[n++] = data;
//			}
//			lastdata = data;
//		}				
//}

//void USART6_IRQHandler(void)                
//{
//	static int n=0;
//	static uint8_t data,lastdata;
//  if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET) 
//    {
//			USART_ClearFlag(USART6, USART_FLAG_RXNE);
//			data = USART_ReceiveData(USART6);
//			if((lastdata == '\\')&&(data == 'n'))
//			{
//				for(int i = 0;i < n-1;i++)
//				{
////				USART6_RX[i] = USART6_RX_BUF[i];
//				}
//				n=0;
//			}
//			else
//			{
//				USART6_RX_BUF[n++] = data;
//			}
//			lastdata = data;
//		}				
//}

//void UART7_IRQHandler(void)                
//{
//	static int n=0;
//	static uint8_t data,lastdata;
//  if(USART_GetITStatus(UART7, USART_IT_RXNE) != RESET) 
//    {
//			USART_ClearFlag(UART7, USART_FLAG_RXNE);
//			data = USART_ReceiveData(UART7);
//			if((lastdata == '\\')&&(data == 'n'))
//			{
//				for(int i = 0;i < n-1;i++)
//				{
//				UART7_RX[i] = UART7_RX_BUF[i];
//				}
//				n=0;
//			}
//			else
//			{
//				UART7_RX_BUF[n++] = data;
//				lastdata = data;
//			}
//			
//		}				
//}

//void UART8_IRQHandler(void)                
//{
//	static int n=0;
//	static uint8_t data,lastdata;
//  if(USART_GetITStatus(UART8, USART_IT_RXNE) != RESET) 
//    {
//			USART_ClearFlag(UART8, USART_FLAG_RXNE);
//			data = USART_ReceiveData(UART8);
//			if((lastdata == '\\')&&(data == 'n'))
//			{
//				for(int i = 0;i < n-1;i++)
//				{
//				UART8_RX[i] = UART8_RX_BUF[i];
//				}
//				n=0;
//			}
//			else
//			{
//				UART8_RX_BUF[n++] = data;
//			}
//			lastdata = data;
//		}				
//}
void USART1_SendData(uint8_t data)
{
    USART_SendData(USART1,data);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void USART2_SendData(uint8_t data)
{
    USART_SendData(USART2,data);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

void USART3_SendData(uint8_t data)
{
    USART_SendData(USART3,data);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}

void USART6_SendData(uint8_t data)
{
    USART_SendData(USART6,data);
		while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
}

void USART7_SendData(uint8_t data)
{
    USART_SendData(UART7,data);
		while (USART_GetFlagStatus(UART7, USART_FLAG_TC) == RESET);
}



void USART8_SendChar(unsigned char b)
{
    while (USART_GetFlagStatus(UART8,USART_FLAG_TC) == RESET);
	USART_SendData(UART8,b);
}

void USART1_printf (char *fmt, ...)
{
	char buffer[256];
	u8 i = 0;

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	vsnprintf(buffer, 256, fmt, arg_ptr);
	while ((i < 255) && buffer[i])
	{
		USART_SendData(USART1, (u8) buffer[i++]);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
	va_end(arg_ptr);
}
 
void USART2_printf (char *fmt, ...)
{
	char buffer[256];
	u8 i = 0;

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	vsnprintf(buffer, 256, fmt, arg_ptr);
	while ((i < 255) && buffer[i])
	{
		USART_SendData(USART2, (u8) buffer[i++]);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	}
	va_end(arg_ptr);
}

void USART3_printf (char *fmt, ...)
{
	char buffer[256];
	u8 i = 0;

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	vsnprintf(buffer, 256, fmt, arg_ptr);
	while ((i < 255) && buffer[i])
	{
		USART_SendData(USART3, (u8) buffer[i++]);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}
	va_end(arg_ptr);
}

void USART6_printf (char *fmt, ...)
{
	char buffer[256];
	u8 i = 0;

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	vsnprintf(buffer, 256, fmt, arg_ptr);
	while ((i < 255) && buffer[i])
	{
		USART_SendData(USART6, (u8) buffer[i++]);
		while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
	}
	va_end(arg_ptr);
}

void UART7_printf (char *fmt, ...)
{
	char buffer[256];
	u8 i = 0;

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	vsnprintf(buffer, 256, fmt, arg_ptr);
	while ((i < 255) && buffer[i])
	{
		USART_SendData(UART7, (u8) buffer[i++]);
		while (USART_GetFlagStatus(UART7, USART_FLAG_TC) == RESET);
	}
	va_end(arg_ptr);
}

void UART8_printf (char *fmt, ...)
{
	char buffer[256];
	u8 i = 0;

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	vsnprintf(buffer, 256, fmt, arg_ptr);
	while ((i < 255) && buffer[i])
	{
		USART_SendData(UART8, (u8) buffer[i++]);
		while (USART_GetFlagStatus(UART8, USART_FLAG_TC) == RESET);
	}
	va_end(arg_ptr);
}

