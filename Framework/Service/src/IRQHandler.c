/**
  ******************************************************************************
  * @file    IRQHandler.c
  * @author  JackyJuu,  site:www.robomentor.cn
	* @Note 		
  * @version V1.0.0
  ******************************************************************************
	* @describe 中断函数处理
*/
#include "stm32f4xx.h"
#include "uart.h"
#include "djirc.h"
#include "user_code.h"

#if DJI_Remote_Control == 0
void USART1_IRQHandler(void)                
{
	volatile static uint8_t data;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    {
			data = USART_ReceiveData(USART1);	
#if RoboMentor_Board_Mission == 1
			RoboMentor_uart_process(data,USART_1);	
#endif		
//用户函数编写处
				
		}				
}
#endif

void USART2_IRQHandler(void)                
{
	volatile static uint8_t data;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
    {
			data = USART_ReceiveData(USART2);	
#if RoboMentor_Board_Mission == 1
			RoboMentor_uart_process(data,USART_2);
#endif		
//用户函数编写处


			
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
//用户函数编写处


			
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
//用户函数编写处


		
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
//用户函数编写处


					
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
//用户函数编写处


			
		}				
}

#if DJI_Remote_Control == 1

/*
*************遥控器数据结构体*************
@Note 	需要使用遥控器相关数据的时候
				需要先引用其他页面中的RC_Ctl变量
				extern RC_Ctl_t RC_Ctl;
				然后直接用RC_Ctl结构体中的数据即可
******************************************
*/
volatile  RC_Ctl_t RC_Ctl;
//****************************************

extern unsigned char sbus_rx_buffer[25]; 
void DMA2_Stream5_IRQHandler(void)
{              
    if(DMA_GetITStatus(DMA2_Stream5, DMA_IT_TCIF5))
    {
        DMA_ClearFlag(DMA2_Stream5, DMA_FLAG_TCIF5);
        DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TCIF5);
				
				RC_Ctl.rc.ch0 = (sbus_rx_buffer[0]| (sbus_rx_buffer[1] << 8)) & 0x07ff;          	//
				RC_Ctl.rc.ch1 = ((sbus_rx_buffer[1] >> 3) | (sbus_rx_buffer[2] << 5)) & 0x07ff;   //    
				RC_Ctl.rc.ch2 = ((sbus_rx_buffer[2] >> 6) | (sbus_rx_buffer[3] << 2) | (sbus_rx_buffer[4] << 10)) & 0x07ff;          
				RC_Ctl.rc.ch3 = ((sbus_rx_buffer[4] >> 1) | (sbus_rx_buffer[5] << 7)) & 0x07ff;   //  
				RC_Ctl.rc.ch4 = sbus_rx_buffer[16] | (sbus_rx_buffer[17] << 8);                 	//左上角波轮      
				RC_Ctl.rc.s1  = ((sbus_rx_buffer[5] >> 4)& 0x000C) >> 2;                          // 
				RC_Ctl.rc.s2  = ((sbus_rx_buffer[5] >> 4)& 0x0003);    														//
				
			
				RC_Ctl.mouse.x = sbus_rx_buffer[6] | (sbus_rx_buffer[7] << 8);                    //鼠标x轴        
				RC_Ctl.mouse.y = sbus_rx_buffer[8] | (sbus_rx_buffer[9] << 8);                    //鼠标y轴     
				RC_Ctl.mouse.z = sbus_rx_buffer[10] | (sbus_rx_buffer[11] << 8);                  //鼠标Z轴         
				RC_Ctl.mouse.press_l = sbus_rx_buffer[12];                                        //鼠标左键  
				RC_Ctl.mouse.press_r = sbus_rx_buffer[13];                                        //鼠标右键
				RC_Ctl.key.v = sbus_rx_buffer[14] | (sbus_rx_buffer[15] << 8);   									//键盘按键值					
						
    }
}

#endif
