#ifndef __PWM_H__
#define __PWM_H__
#include "stm32f4xx.h"

/* 
* APB1 prescaler = 4, APB1 TIMER Frequency = 2*45 = 90MHz
* APB2 prescaler = 2, APB2 TIMER Frequency = 2*90 = 180MHz
*/
#define TIM_PSC_APB1 ((APB1_TIMER_CLOCKS/PWM_FREQUENCE)/PWM_RESOLUTION -1)
#define PWM_FREQUENCE 107             //时钟有误差，取107分下来正好     
#define PWM_RESOLUTION 5000         // 50hz,SERVO_DEFAULT_DUTY = 1500ms* 50 / 100
#define SERVO_DEFAULT_DUTY 750      // 50hz,1500us,1.5ms
#define TIM_PSC_APB2 ((APB2_TIMER_CLOCKS/PWM_FREQUENCE)/PWM_RESOLUTION -1)
#define APB1_TIMER_CLOCKS 90000000
#define APB2_TIMER_CLOCKS 180000000


void TIM1_Init(void);
void TIM8_Init(void);
void TIM2_Init(void);
void TIM4_Init(void);
void TIM5_Init(void);

typedef enum
{
	PD12 = 1,
	PD13 = 2,
	PD14 = 3,
	PD15 = 4,
	PH10 = 5,
	PH11 = 6,
	PH12 = 7,
	PI0 = 8,
	PA0 = 9,
	PA1 = 10,
	PA2 = 11,
	PA3 = 12,
	PI5 = 13,
	PI6 = 14,
	PI7 = 15,
	PI2 = 16,
	ALL_PWM_Channel
}PWM_Channel_t;

typedef enum
{
	Mode_In,
	Mode_Out,
	Mode_PWM_Up,
	Mode_PWM_Down
}PWM_Mode_t;

typedef enum
{
	PWM_IO_High,
	PWM_IO_Low,
	PWM_IO_Toggle	
}PWM_Out_t;

void PWM_Io_Init(PWM_Channel_t PWM_Channel,PWM_Mode_t PWM_Mode);
void PWM_Set(PWM_Channel_t PWM_Channel,uint16_t psc,uint16_t pwm);
void PWM_Out_Set(PWM_Channel_t PWM_Channel,PWM_Out_t PWM_Out);
int PWM_Io_Scan(PWM_Channel_t PWM_Channel);


typedef enum
{
	PWM_CounterMode_Up,
	PWM_CounterMode_Down
}PWM_CounterMode_t;

typedef enum
{
	PWMO_OCMode_PWM1,
	PWM_OCMode_PWM2
}PWM_OCMode_t;

typedef enum
{
	PWM_OCPolarity_High,
	PWM_OCPolarity_Low
}PWM_OCPolarity_t;

void TIM1_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity);
void TIM8_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity);
void TIM2_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity);
void TIM4_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity);
void TIM5_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity);

#endif

