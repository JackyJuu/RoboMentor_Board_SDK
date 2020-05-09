#ifndef __POWER_H__
#define __POWER_H__
typedef enum
{
	Power_ON,
	Power_OFF
}Power_State_t;

typedef enum
{
	Power_24V_Channel_1 = 1,
	Power_24V_Channel_2 = 2,
	Power_24V_Channel_3 = 3,
	Power_24V_Channel_4 = 4
}Power_24V_Channel_t;


typedef enum
{
	Power_5V_Channel_1,
	Power_5V_Channel_2
}Power_5V_Channel_t;



void Power_24V_Init(void);
void Power_5v_Init(void);

void Power_24v_switch(Power_24V_Channel_t Power_24V_Channel,Power_State_t Power_State);
void Power_5v_switch(Power_5V_Channel_t Power_5V_Channel,Power_State_t Power_State);

#endif
