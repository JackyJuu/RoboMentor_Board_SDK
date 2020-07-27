#include "stm32f4xx.h"
#include "can.h"
#include "delay.h"
#include "Mission_task.h"

uint8_t CAN1_RX_DATA[8];
int16_t CAN1_RX_STDID;
int CAN1_RX_FLAG = 1;

extern int can1_rx_stdid;
extern int can2_rx_stdid;

CanRxMsg can2_receive_message;
CanRxMsg can1_receive_message;



/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
void CAN1_Init(void)
{
  GPIO_InitTypeDef 		  GPIO_InitStructure;
	CAN_InitTypeDef   		CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
  
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	/* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
		
  /* CAN register init */
  CAN_DeInit(CAN1);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    
  /* CAN Baudrate = 1 MBps (CAN clocked at 30 MHz) */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
  CAN_InitStructure.CAN_Prescaler = 3;
  CAN_Init(CAN1, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
  CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
void CAN2_Init(void)
{
  GPIO_InitTypeDef 		  GPIO_InitStructure;
	CAN_InitTypeDef   		CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
  
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	/* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
  /* CAN register init */
  CAN_DeInit(CAN2);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    
  /* CAN Baudrate = 1 MBps (CAN clocked at 30 MHz) */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
  CAN_InitStructure.CAN_Prescaler = 3;
  CAN_Init(CAN2, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
  CAN_ITConfig(CAN2, CAN_IT_TME, ENABLE); 
}

void CAN1_Send(int16_t Stdid,uint8_t * data)     //车轮电机
{
    CanTxMsg tx_message;
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.DLC = 0x08;          //帧长度为   
	
		tx_message.StdId = Stdid;
		tx_message.Data[0] = data[0];
		tx_message.Data[1] = data[1];
    tx_message.Data[2] = data[2];
    tx_message.Data[3] = data[3];
		tx_message.Data[4] = data[4];
    tx_message.Data[5] = data[5];
		tx_message.Data[6] = data[6];
    tx_message.Data[7] = data[7];
		
    CAN_Transmit(CAN1,&tx_message);
}

void CAN2_Send(int16_t Stdid,uint8_t * data)     //车轮电机
{
    CanTxMsg tx_message;
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.DLC = 0x08;          //帧长度为   
	
		tx_message.StdId = Stdid;
		tx_message.Data[0] = data[0];
		tx_message.Data[1] = data[1];
    tx_message.Data[2] = data[2];
    tx_message.Data[3] = data[3];
		tx_message.Data[4] = data[4];
    tx_message.Data[5] = data[5];
		tx_message.Data[6] = data[6];
    tx_message.Data[7] = data[7];
		
    CAN_Transmit(CAN2,&tx_message);
}

void CAN1_Rx_Get(int16_t stdid,uint8_t * data)
{
	if(can1_receive_message.StdId == stdid)
	{
		data[0] = can1_receive_message.Data[0];
		data[1] = can1_receive_message.Data[1];
		data[2] = can1_receive_message.Data[2];
		data[3] = can1_receive_message.Data[3];
		data[4] = can1_receive_message.Data[4];
		data[5] = can1_receive_message.Data[5];
		data[6] = can1_receive_message.Data[6];
		data[7] = can1_receive_message.Data[7];
	}
}

void CAN2_Rx_Get(int16_t stdid,uint8_t * data)
{
	if(can2_receive_message.StdId == stdid)
	{
		data[0] = can2_receive_message.Data[0];
		data[1] = can2_receive_message.Data[1];
		data[2] = can2_receive_message.Data[2];
		data[3] = can2_receive_message.Data[3];
		data[4] = can2_receive_message.Data[4];
		data[5] = can2_receive_message.Data[5];
		data[6] = can2_receive_message.Data[6];
		data[7] = can2_receive_message.Data[7];
	}
}


void CAN1_Motor_Control(int16_t stdid,u16 num1,u16 num2,u16 num3,u16 num4)
{
    CanTxMsg tx_message;
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.DLC = 0x08;          //帧长度为   
		tx_message.StdId = stdid;
		tx_message.Data[0] =(unsigned char)((num1>> 8)&0xff);
		tx_message.Data[1] =(unsigned char)(num1&0xff);
    tx_message.Data[2] =(unsigned char)((num2 >> 8)&0xff);
    tx_message.Data[3] =(unsigned char)(num2&0xff);
		tx_message.Data[4] =(unsigned char)((num3 >> 8)&0xff);
    tx_message.Data[5] =(unsigned char)(num3&0xff);
		tx_message.Data[6] =(unsigned char)((num4 >> 8)&0xff);
    tx_message.Data[7] =(unsigned char)(num4&0xff);
	
   CAN_Transmit(CAN1,&tx_message);
}


void CAN2_Motor_Control(int16_t stdid,u16 num1,u16 num2,u16 num3,u16 num4)
{
    CanTxMsg tx_message;
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.DLC = 0x08;          //帧长度为   
		tx_message.StdId = stdid;
		tx_message.Data[0] =(unsigned char)((num1>> 8)&0xff);
		tx_message.Data[1] =(unsigned char)(num1&0xff);
    tx_message.Data[2] =(unsigned char)((num2 >> 8)&0xff);
    tx_message.Data[3] =(unsigned char)(num2&0xff);
		tx_message.Data[4] =(unsigned char)((num3 >> 8)&0xff);
    tx_message.Data[5] =(unsigned char)(num3&0xff);
		tx_message.Data[6] =(unsigned char)((num4 >> 8)&0xff);
    tx_message.Data[7] =(unsigned char)(num4&0xff);
	
   CAN_Transmit(CAN2,&tx_message);
}


void CAN1_Motor_Get(int16_t stdid,int* angle,int* speed,int* current,float* temperature)
{
	volatile int num_ch;
	if(can1_receive_message.StdId == stdid)
	{
			*angle=(int)(can1_receive_message.Data[0] << 8) + (can1_receive_message.Data[1]);//电机机械角度值 
			num_ch = (int)(can1_receive_message.Data[2] << 8) + (can1_receive_message.Data[3]);//电机速度值
			if(num_ch > 32448)
			{*speed = num_ch - 65535;}
			else
			{*speed = num_ch;}	
			num_ch = (int)(can1_receive_message.Data[4] << 8) + (can1_receive_message.Data[5]);//电机转矩电流
			if(num_ch > 32448)
			{*current = num_ch - 65535;}
			else
			{*current = num_ch;}
			*temperature = (double)(can1_receive_message.Data[6]);
	}
}

void CAN2_Motor_Get(int16_t stdid,int* angle,int* speed,int* current,float* temperature)
{
	volatile int num_ch;
	if(can2_receive_message.StdId == stdid)
	{
			*angle=(int)(can2_receive_message.Data[0] << 8) + (can2_receive_message.Data[1]);//电机机械角度值 
			num_ch = (int)(can2_receive_message.Data[2] << 8) + (can2_receive_message.Data[3]);//电机速度值
			if(num_ch > 32448)
			{*speed = num_ch - 65535;}
			else
			{*speed = num_ch;}	
			num_ch = (int)(can2_receive_message.Data[4] << 8) + (can2_receive_message.Data[5]);//电机转矩电流
			if(num_ch > 32448)
			{*current = num_ch - 65535;}
			else
			{*current = num_ch;}
			*temperature = (double)(can2_receive_message.Data[6]);
	}
}

/*************************************************************************
                          CAN1_RX0_IRQHandler
描述：CAN1的接收中断函数
*************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)	//判断是否接收结束
		{
				CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);		//清除FIFO0消息挂号中断标志位
        CAN_Receive(CAN1, CAN_FIFO0, &can1_receive_message);	//获取接收数据
				Can_1_ReceiveMsgProcess(&can1_receive_message,can1_rx_stdid);       		//将数据通过函数处理
    }
}

/*************************************************************************
                          CAN2_RX0_IRQHandler
描述：CAN2的接收中断函数
*************************************************************************/
void CAN2_RX0_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)	//判断是否接收结束
		{
				CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);		//清除FIFO0消息挂号中断标志位
        CAN_Receive(CAN2, CAN_FIFO0, &can2_receive_message);	//获取接收数据
				Can_2_ReceiveMsgProcess(&can2_receive_message,can2_rx_stdid);       		//将数据通过函数处理
    }
}




