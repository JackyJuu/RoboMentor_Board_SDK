#ifndef __USART_STEERING_H__
#define __USART_STEERING_H__
#include "stm32f4xx.h"
#include "uart.h"

typedef enum {
	false = 0, true = !false
}bool;


#define GET_LOW_BYTE(A) ((uint8_t)(A))
//�꺯�� ���A�ĵͰ�λ
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
//�꺯�� ���A�ĸ߰�λ
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//�꺯�� ���ߵذ�λ�ϳ�Ϊʮ��λ

#define SERVO_FRAME_HEADER         0x55
#define SERVO_MOVE_TIME_WRITE      1
#define SERVO_MOVE_TIME_READ       2
#define SERVO_MOVE_TIME_WAIT_WRITE 7
#define SERVO_MOVE_TIME_WAIT_READ  8
#define SERVO_MOVE_START           11
#define SERVO_MOVE_STOP            12
#define SERVO_ID_WRITE             13
#define SERVO_ID_READ              14
#define SERVO_ANGLE_OFFSET_ADJUST  17
#define SERVO_ANGLE_OFFSET_WRITE   18
#define SERVO_ANGLE_OFFSET_READ    19
#define SERVO_ANGLE_LIMIT_WRITE    20
#define SERVO_ANGLE_LIMIT_READ     21
#define SERVO_VIN_LIMIT_WRITE      22
#define SERVO_VIN_LIMIT_READ       23
#define SERVO_TEMP_MAX_LIMIT_WRITE 24
#define SERVO_TEMP_MAX_LIMIT_READ  25
#define SERVO_TEMP_READ            26
#define SERVO_VIN_READ             27
#define SERVO_POS_READ             28
#define SERVO_OR_MOTOR_MODE_WRITE  29
#define SERVO_OR_MOTOR_MODE_READ   30
#define SERVO_LOAD_OR_UNLOAD_WRITE 31
#define SERVO_LOAD_OR_UNLOAD_READ  32
#define SERVO_LED_CTRL_WRITE       33
#define SERVO_LED_CTRL_READ        34
#define SERVO_LED_ERROR_WRITE      35
#define SERVO_LED_ERROR_READ       36

#define DEBUG 1


typedef enum
{
	STEERING_READ_MODE = 0,//��ȡ���߶��ģʽ
	STEERING_READ_ID,//��ȡ���߶��ID
	STEERING_ANGLE_OFFSET_READ,//��ȡ���߶��ƫ��ֵ
	STEERING_ANGLE_LIMIT_READ,//��ȡ���߶���Ƕȷ�Χ
	STEERING_VIN_LIMIT_READ,//��ȡ���߶����ѹ��Χ
	STEERING_MOTION_READ,//���߶���˶�״̬��ȡ
	STEERING_VIN_READ,//��ȡ���߶����ǰ�����ѹ
	STEERING_POS_READ//��ȡ���߶����ǰλ�ýǶ�����
}Steering_Read_Mode_t;

extern uint8_t LobotRxBuf[16];

uint8_t LobotCheckSum(uint8_t buf[]);
void LobotSerialServoSetID(uint8_t oldID, uint8_t newID);
void LobotSerialServoMove(uint8_t id, int16_t position, uint16_t time);
void LobotSerialServoUnload(uint8_t id);
void LobotSerialServoLoad(uint8_t id);
int LobotSerialServoReadPosition(uint8_t id);
int LobotSerialMsgHandle(void);

//�������߶��ģʽ
void Steerint_Mode_Set(uint8_t id,uint8_t mode,uint16_t speed,USART_t USART);
//��ȡ���߶��ģʽ
void Steerint_Mode_Read(uint8_t id,USART_t USART);
//�������߶��ID
void Steerint_ID_Set(uint8_t old_id,uint8_t new_id,USART_t USART);
//��ȡ���߶��ID
void Steerint_ID_Read(USART_t USART);
//�������߶��ƫ��ֵ
void Steerint_Angle_Offset_Write(uint8_t id,uint8_t value,USART_t USART);
//��ȡ���߶��ƫ��ֵ
void Steerint_Angle_Offset_Read(uint8_t id,USART_t USART);
//�������߶���Ƕȷ�Χ
void Steerint_Angle_Limit_Set(uint8_t id,uint16_t min_angle,uint16_t max_angle,USART_t USART);
//��ȡ���߶���Ƕȷ�Χ
void Steerint_Angle_Limit_Read(uint8_t id,USART_t USART);
//�������߶����ѹ��Χ
void Steerint_Vin_Limit_Set(uint8_t id,uint16_t min_vin,uint16_t max_vin,USART_t USART);
//��ȡ���߶����ѹ��Χ
void Steerint_Vin_Limit_Read(uint8_t id,USART_t USART);
//���߶�����˶�����
void Steerint_Motion_Set(uint8_t id, int16_t position,uint16_t time,USART_t USART);
//���߶���˶�״̬��ȡ
void Steerint_Motion_Read(uint8_t id,USART_t USART);
//���߶��ֹͣ�˶�
void Steerint_Stop_Motion(uint8_t id,USART_t USART);
//��ȡ���߶����ǰ�����ѹ
void Steerint_Vin_Read(uint8_t id,USART_t USART);
//��ȡ���߶����ǰλ�ýǶ�����
void Steerint_Now_Angle_Read(uint8_t id,USART_t USART);


void uartInit(u32 bound);
void uartWriteBuf(uint8_t *buf, uint8_t len);
bool isRxCompleted(void);

#endif
