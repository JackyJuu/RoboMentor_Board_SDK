#ifndef __UART_H__
#define __UART_H__
#include "stm32f4xx.h"


typedef enum
{
	Usart_Rx = USART_Mode_Rx,
	Usart_Tx = USART_Mode_Tx,
	Usart_TxRx = USART_Mode_Rx | USART_Mode_Tx
}Usart_Mode_t;

typedef enum
{
	Usart_Parity_No = USART_Parity_No,
	Usart_Parity_Even = USART_Parity_Even,
	Usart_Parity_Odd = USART_Parity_Odd
}Usart_Parity_t;

typedef enum
{
	USART_1,
	USART_2,
	USART_3,
	USART_4,
	USART_6,
	UART_7,
	UART_8
}USART_t;

void USART1_Init(void);
void USART2_Init(void);
void USART3_Init(void);
void USART6_Init(void);
void UART7_Init(void);
void UART8_Init(void);

void USART1_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity);
void USART2_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity);
void USART3_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity);
void USART6_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity);
void UART7_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity);
void UART8_Config(int BaudRate,Usart_Mode_t Usart_Mode,Usart_Parity_t Usart_Parity);

void RoboMentor_uart_process(uint8_t data,USART_t USART);

void USART1_SendData(uint8_t data);
void USART2_SendData(uint8_t data);
void USART3_SendData(uint8_t data);
void USART6_SendData(uint8_t data);
void UART7_SendData(uint8_t data);
void UART8_SendData(uint8_t data);

void USART1_printf (char *fmt, ...);
void USART2_printf (char *fmt, ...);
void USART3_printf (char *fmt, ...);
void USART6_printf (char *fmt, ...);
void UART7_printf (char *fmt, ...);
void UART8_printf (char *fmt, ...);
				



#endif
