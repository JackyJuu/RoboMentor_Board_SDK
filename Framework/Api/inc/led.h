#ifndef __LED_H__
#define __LED_H__
#include "stm32f4xx.h"

void Led_Init(void);
void Test_LED(void);

typedef enum
{
	ON = 0,
	OFF = 1,
	TOGGLE = 2
}LED_status_t;

void LED_Green_Switch(LED_status_t LED_status);
void LED_Red_Switch(LED_status_t LED_status);
void LED_Blue_Switch(LED_status_t LED_status);

#endif
