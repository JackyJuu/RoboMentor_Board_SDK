#include "Start_Task.h"
#include "user_code.h"
#include "Robomentor_task.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "led.h"
#include "uart.h"
#include "mpu_9250.h"
#include "adc.h"
#include "sd_card.h"

#include "stm32fxxx_it.h"

#include "usbd_cdc_vcp.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE 512
static TaskHandle_t StartTask_Handler;

#if User_Mission_1 == 1
#define USER1_TASK_PRIO 11
#define USER1_STK_SIZE 512
static TaskHandle_t User1Task_Handler;
#endif

#if User_Mission_2 == 1
#define USER2_TASK_PRIO 10
#define USER2_STK_SIZE 512
static TaskHandle_t User2Task_Handler;
#endif

#if User_Mission_3 == 1
#define USER3_TASK_PRIO 9
#define USER3_STK_SIZE 512
static TaskHandle_t User3Task_Handler;
#endif

#if User_Mission_4 == 1
#define USER4_TASK_PRIO 8
#define USER4_STK_SIZE 512
static TaskHandle_t User4Task_Handler;
#endif

#if User_Mission_5 == 1
#define USER5_TASK_PRIO 7
#define USER5_STK_SIZE 512
static TaskHandle_t User5Task_Handler;
#endif



void start_task(void *pvParameters)
{							
    taskENTER_CRITICAL();
	
	
#if RoboMentor_Board_Mission == 1
	robomentor_board();
#endif
	
#if User_Mission_1 == 1
		 xTaskCreate((TaskFunction_t)user1_task,          //������
                (const char *)"user1_task",          //��������
                (uint16_t)USER1_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)USER1_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&User1Task_Handler); //������	
#endif

#if User_Mission_2 == 1								
		 xTaskCreate((TaskFunction_t)user2_task,          //������
                (const char *)"user2_task",          //��������
                (uint16_t)USER2_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)USER2_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&User2Task_Handler); //������	
#endif
	
#if User_Mission_3 == 1								
		 xTaskCreate((TaskFunction_t)user3_task,          //������
                (const char *)"user3_task",          //��������
                (uint16_t)USER3_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)USER3_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&User3Task_Handler); //������	
#endif
		
#if User_Mission_4 == 1								
		 xTaskCreate((TaskFunction_t)user4_task,          //������
                (const char *)"user4_task",          //��������
                (uint16_t)USER4_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)USER4_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&User4Task_Handler); //������	
#endif

#if User_Mission_5 == 1								
		 xTaskCreate((TaskFunction_t)user5_task,          //������
                (const char *)"user5_task",          //��������
                (uint16_t)USER5_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)USER5_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&User5Task_Handler); //������									
#endif	
	
		vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

void startTast(void)
{
    xTaskCreate((TaskFunction_t)start_task,          //������
                (const char *)"start_task",          //��������
                (uint16_t)START_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)START_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&StartTask_Handler); //������								
}

