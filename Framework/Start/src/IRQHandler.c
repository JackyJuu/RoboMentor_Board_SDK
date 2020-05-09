#include "stm32f4xx.h"
#include "uart.h"


void USART1_IRQHandler(void)                
{
	volatile static uint8_t data;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    {
			data = USART_ReceiveData(USART1);	
#if RoboMentor_Board_Mission == 1
			RoboMentor_uart_process(data,USART_1);	
#endif		
//�û�������д��

			
		}				
}

void USART2_IRQHandler(void)                
{
	volatile static uint8_t data;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
    {
			data = USART_ReceiveData(USART2);	
#if RoboMentor_Board_Mission == 1
			RoboMentor_uart_process(data,USART_2);
#endif		
//�û�������д��


			
		}				
}

void USART3_IRQHandler(void)                
{
	volatile static uint8_t data;
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
    {
			data = USART_ReceiveData(USART3);	
#if RoboMentor_Board_Mission == 1
			RoboMentor_uart_process(data,USART_3);
#endif		
//�û�������д��


			
		}				
}

void USART6_IRQHandler(void)                
{
	volatile static uint8_t data;
  if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET) 
    {
			data = USART_ReceiveData(USART6);	
#if RoboMentor_Board_Mission == 1			
			RoboMentor_uart_process(data,USART_6);
#endif			
//�û�������д��


		
		}				
}

void UART7_IRQHandler(void)                
{
	volatile static uint8_t data;
  if(USART_GetITStatus(UART7, USART_IT_RXNE) != RESET) 
    {
			data = USART_ReceiveData(UART7);	
#if RoboMentor_Board_Mission == 1
			RoboMentor_uart_process(data,UART_7);
#endif		
//�û�������д��


					
		}				
}

void UART8_IRQHandler(void)                
{
	volatile static uint8_t data;
  if(USART_GetITStatus(UART8, USART_IT_RXNE) != RESET) 
    {
			data = USART_ReceiveData(UART8);	
#if RoboMentor_Board_Mission == 1
			RoboMentor_uart_process(data,UART_8);
#endif	
//�û�������д��


			
		}				
}
