#ifndef USER_CODE_H
#define USER_CODE_H

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx.h"

#define RoboMentor_Board_Mission 0

#define User_Mission_1 1
#define User_Mission_2 1
#define User_Mission_3 1
#define User_Mission_4 1
#define User_Mission_5 1


#define user1_main(void) user1_task(void *pvParameters)
#define user2_main(void) user2_task(void *pvParameters)
#define user3_main(void) user3_task(void *pvParameters)
#define user4_main(void) user4_task(void *pvParameters)
#define user5_main(void) user5_task(void *pvParameters)

#if User_Mission_1 == 1
void user1_task(void *pvParameters);
#endif

#if User_Mission_2 == 1
void user2_task(void *pvParameters);
#endif

#if User_Mission_3 == 1
void user3_task(void *pvParameters);
#endif

#if User_Mission_4 == 1
void user4_task(void *pvParameters);
#endif

#if User_Mission_5 == 1
void user5_task(void *pvParameters);
#endif



#endif

