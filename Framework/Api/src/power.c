#include "stm32f4xx.h"
#include "power.h"
#include "delay.h"
#include "All_define.h"


void Power_24V_Init(void)
{
  GPIO_InitTypeDef gpio;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_2 |  GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOH,&gpio);
	
	
	
	POWER1_24V_OFF();
	POWER2_24V_OFF();
	POWER3_24V_OFF();
	POWER4_24V_OFF();
}

void Power_5v_Init(void)
{
  GPIO_InitTypeDef gpio;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_15;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_11;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&gpio);

	POWER_5V_A_OFF();
	POWER_5V_B_OFF();
}

void Power_24v_switch(Power_24V_Channel_t Power_24V_Channel,Power_State_t Power_State)
{
	switch(Power_24V_Channel)
	{
		case Power_24V_Channel_1:
		{
			if(Power_State == Power_ON)
			POWER1_24V_ON();
			else if(Power_State == Power_OFF)
			POWER1_24V_OFF();
		break;
		}
		case Power_24V_Channel_2:
		{
			if(Power_State == Power_ON)
			POWER2_24V_ON();
			else if(Power_State == Power_OFF)
			POWER2_24V_OFF();
		break;
		}
		case Power_24V_Channel_3:
		{
			if(Power_State == Power_ON)
			POWER3_24V_ON();
			else if(Power_State == Power_OFF)
			POWER3_24V_OFF();
		break;
		}
		case Power_24V_Channel_4:
		{
			if(Power_State == Power_ON)
			POWER4_24V_ON();
			else if(Power_State == Power_OFF)
			POWER4_24V_OFF();
		break;
		}
	}
}

void Power_5v_switch(Power_5V_Channel_t Power_5V_Channel,Power_State_t Power_State)
{
	switch(Power_5V_Channel)
	{
		case Power_5V_Channel_1:
		{
			if(Power_State == Power_ON)
			POWER_5V_A_ON();
			else if(Power_State == Power_OFF)
			POWER_5V_A_OFF();
		break;
		}
		case Power_5V_Channel_2:
		{
			if(Power_State == Power_ON)
			POWER_5V_B_ON();
			else if(Power_State == Power_OFF)
			POWER_5V_B_OFF();
		break;
		}
	}
}
