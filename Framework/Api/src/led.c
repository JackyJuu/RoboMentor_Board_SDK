#include "stm32f4xx.h"
#include "led.h"
#include "All_define.h"
#include "delay.h"

void Led_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOH,&GPIO_InitStructure);
	
    
  GREEN_LED_OFF();
  RED_LED_OFF();
	BLUE_LED_OFF();
}

void LED_Green_Switch(LED_status_t LED_status)
{
	if(LED_status == ON)
	{
		GREEN_LED_ON();
	}
	else if (LED_status == OFF)
	{
		GREEN_LED_OFF();
	}
	else if (LED_status == TOGGLE)
	{
		GREEN_LED_TOGGLE();
	}
}

void LED_Red_Switch(LED_status_t LED_status)
{
	if(LED_status == ON)
	{
		RED_LED_ON();
	}
	else if (LED_status == OFF)
	{
		RED_LED_OFF();
	}
	else if (LED_status == TOGGLE)
	{
		RED_LED_TOGGLE();
	}
}

void LED_Blue_Switch(LED_status_t LED_status)
{
	if(LED_status == ON)
	{
		BLUE_LED_ON();
	}
	else if (LED_status == OFF)
	{
		BLUE_LED_OFF();
	}
	else if (LED_status == TOGGLE)
	{
		BLUE_LED_TOGGLE();
	}
}




void Test_LED(void)
{
	GREEN_LED_TOGGLE();
	RED_LED_TOGGLE();
	BLUE_LED_TOGGLE();
}
