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
		 xTaskCreate((TaskFunction_t)user1_task,          //任务函数
                (const char *)"user1_task",          //任务名称
                (uint16_t)USER1_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)USER1_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&User1Task_Handler); //任务句柄	
#endif

#if User_Mission_2 == 1								
		 xTaskCreate((TaskFunction_t)user2_task,          //任务函数
                (const char *)"user2_task",          //任务名称
                (uint16_t)USER2_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)USER2_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&User2Task_Handler); //任务句柄	
#endif
	
#if User_Mission_3 == 1								
		 xTaskCreate((TaskFunction_t)user3_task,          //任务函数
                (const char *)"user3_task",          //任务名称
                (uint16_t)USER3_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)USER3_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&User3Task_Handler); //任务句柄	
#endif
		
#if User_Mission_4 == 1								
		 xTaskCreate((TaskFunction_t)user4_task,          //任务函数
                (const char *)"user4_task",          //任务名称
                (uint16_t)USER4_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)USER4_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&User4Task_Handler); //任务句柄	
#endif

#if User_Mission_5 == 1								
		 xTaskCreate((TaskFunction_t)user5_task,          //任务函数
                (const char *)"user5_task",          //任务名称
                (uint16_t)USER5_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)USER5_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&User5Task_Handler); //任务句柄									
#endif	
	
		vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

void startTast(void)
{
    xTaskCreate((TaskFunction_t)start_task,          //任务函数
                (const char *)"start_task",          //任务名称
                (uint16_t)START_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&StartTask_Handler); //任务句柄								
}

