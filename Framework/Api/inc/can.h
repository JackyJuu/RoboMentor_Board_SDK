#ifndef __CAN_H__
#define __CAN_H__
#include "stm32f4xx.h"
void CAN1_Init(void);
void CAN2_Init(void);

void CAN1_Send(int16_t Stdid,uint8_t * data);
void CAN2_Send(int16_t Stdid,uint8_t * data);
void CAN1_Rx_Get(int16_t stdid,uint8_t * data);
void CAN2_Rx_Get(int16_t stdid,uint8_t * data);

void CAN1_Motor_Control(int16_t stdid,u16 num1,u16 num2,u16 num3,u16 num4);
void CAN2_Motor_Control(int16_t stdid,u16 num1,u16 num2,u16 num3,u16 num4);	
void CAN1_Motor_Get(int16_t stdid,int* angle,int* speed,int* current,float* temperature);
void CAN2_Motor_Get(int16_t stdid,int* angle,int* speed,int* current,float* temperature);



#endif
