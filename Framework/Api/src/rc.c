#include "stm32f4xx.h"
#include "uart.h"
#include "djirc.h"
#include "delay.h"

volatile unsigned char sbus_rx_buffer[25]; 

void DJI_Remote_Control_Init(void)
{
    USART_InitTypeDef usart1;
	  GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;
		DMA_InitTypeDef   dma;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_DMA2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    //GPIO_PinAFConfig(GPIOB,GPIO_PinSource6 ,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1); 
	
    gpio.GPIO_Pin = GPIO_Pin_7;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB,&gpio);
		
		USART_DeInit(USART1);
    usart1.USART_BaudRate = 100000;
    usart1.USART_WordLength = USART_WordLength_8b;
    usart1.USART_StopBits = USART_StopBits_1;
    //usart1.USART_Parity = USART_Parity_No;
		usart1.USART_Parity = USART_Parity_Even;
    //usart1.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
		usart1.USART_Mode =USART_Mode_Rx;
    usart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1,&usart1);

    USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
    USART_Cmd(USART1,ENABLE);
		
		USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
   
	  nvic.NVIC_IRQChannel = DMA2_Stream5_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
		
		DMA_Cmd(DMA2_Stream5, DISABLE);
    while (DMA2_Stream5->CR & DMA_SxCR_EN);
		DMA_DeInit(DMA2_Stream5);
    dma.DMA_Channel= DMA_Channel_4;
    dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
    dma.DMA_Memory0BaseAddr = (uint32_t)sbus_rx_buffer;
    dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
    dma.DMA_BufferSize = 18;
    dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma.DMA_Mode = DMA_Mode_Circular;
    dma.DMA_Priority = DMA_Priority_VeryHigh;
    dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    dma.DMA_MemoryBurst = DMA_Mode_Normal;
    dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream5,&dma);
		
		DMA_ITConfig(DMA2_Stream5,DMA_IT_TC,ENABLE);
    DMA_Cmd(DMA2_Stream5,ENABLE);
		
}




