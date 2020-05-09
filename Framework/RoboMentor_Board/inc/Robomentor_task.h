#ifndef ROBOMENTOR_TASK_H
#define ROBOMENTOR_TASK_H

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

void mpu_task(void *pvParameters);
void robomentor_board(void);

#endif
