#ifndef MISSION_TASK_H
#define MISSION_TASK_H

#include "stm32f4xx.h"
#include "sd_card.h"
#include "ff.h"

typedef struct 
{
	int ole_angle;
	float angle;
	int speed;
	int current;
	float	temperature;
}can_1_motor_message_t;

typedef struct 
{
	int ole_angle;
	float angle;
	int speed;
	int current;
	float	temperature;
}can_2_motor_message_t;

void pwm_set(int channel,uint16_t psc,uint16_t pwm);

void Can1_Tx_Reset(void);
void Can2_Tx_Reset(void);

void Can1_Tx_Mode(void);
void Can2_Tx_Mode(void);

void Can_1_ReceiveMsgProcess(CanRxMsg *can_receive_message,int stdD);
void Can_2_ReceiveMsgProcess(CanRxMsg *can_receive_message,int stdD);

void Tset_CAN1(void);
void Tset_CAN2(void);

void TF_scan(void);
void TF_delete(char* filename_t);	
void TF_add(char* filename_t, char* data);	
void TF_read(char* filename_t);
void TF_write(char* filename_t, char* data);


void mission_task(void *pvParameters);
void song_task(void *pvParameters);

void FR_USB_print_error( FRESULT fresult );

void qianyuqianxun_step(int step);
void little_star_step(int step);

#endif
