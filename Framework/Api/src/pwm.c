#include "pwm.h"
#include "All_define.h"

static void TIM2_Down_Config(void);
static void TIM4_Down_Config(void);
static void TIM5_Down_Config(void);
static void TIM8_Down_Config(void);
static void TIM1_Down_Config(void);

void PWM_Motor_Init(PWM_Motor_Channel_t PWM_Motor_Channel,PWM_Mode_t PWM_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(PWM_Mode == Mode_In)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	}
	else if(PWM_Mode == Mode_Out)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	}
	else if(PWM_Mode == Mode_PWM_Up)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		
		TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
		TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 1500;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	}
	else if(PWM_Mode == Mode_PWM_Down)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		
		TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
		TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 1500;
	}
	
	if(PWM_Motor_Channel == ALL_PWM_Motor_Channel)
	{
		if(PWM_Mode == Mode_PWM_Up)
		{
			TIM1_Config(PWM_RESOLUTION,TIM_PSC_APB2,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);		
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			TIM1_Down_Config();
		}
		else if(PWM_Mode == Mode_In)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			//TIM1
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			//TIM1
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		}
	}
	else if(PWM_Motor_Channel == PA8)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
			GPIO_Init(GPIOA, &GPIO_InitStructure);			
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
			GPIO_Init(GPIOA,&GPIO_InitStructure);
		}
	}
	else if(PWM_Motor_Channel == PA9)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_Init(GPIOA, &GPIO_InitStructure);			
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_Init(GPIOA,&GPIO_InitStructure);
		}
	}
	else if(PWM_Motor_Channel == PE13)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_Init(GPIOE, &GPIO_InitStructure);	
			GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_Init(GPIOE, &GPIO_InitStructure);			
			GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_Init(GPIOE,&GPIO_InitStructure);
		}
	}
	else if(PWM_Motor_Channel == PE14)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			GPIO_Init(GPIOE, &GPIO_InitStructure);	
			GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			GPIO_Init(GPIOE, &GPIO_InitStructure);			
			GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM1, ENABLE);
			TIM_Cmd(TIM1, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			GPIO_Init(GPIOE,&GPIO_InitStructure);
		}
	}
	
	
}


void PWM_Io_Init(PWM_Channel_t PWM_Channel,PWM_Mode_t PWM_Mode)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(PWM_Mode == Mode_In)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	}
	else if(PWM_Mode == Mode_Out)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	}
	else if(PWM_Mode == Mode_PWM_Up)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		
		TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
		TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 1500;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	}
	else if(PWM_Mode == Mode_PWM_Down)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		
		TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
		TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 1500;
	}

	
  if(PWM_Channel == ALL_PWM_Channel)
	{
		if(PWM_Mode == Mode_PWM_Up)
		{
			TIM8_Config(PWM_RESOLUTION,TIM_PSC_APB2,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
			TIM2_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
			TIM4_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
			TIM5_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			TIM2_Down_Config();
			TIM4_Down_Config();
			TIM5_Down_Config();
			TIM8_Down_Config();
		}
		else if(PWM_Mode == Mode_In)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			//TIM5
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
			//TIM4
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			//TIM2
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			//TIM8
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			//TIM5
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
			//TIM4
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			//TIM2
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			//TIM8
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PD12)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_Init(GPIOD, &GPIO_InitStructure);	
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM4, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM4, ENABLE);
			TIM_Cmd(TIM4, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_Init(GPIOD, &GPIO_InitStructure);			
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM4, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM4, ENABLE);
			TIM_Cmd(TIM4, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_Init(GPIOD,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PD13)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);		
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);		
			TIM_OC2Init(TIM4, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM4, ENABLE);
			TIM_Cmd(TIM4, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_Init(GPIOD, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
			TIM_OC2Init(TIM4, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM4, ENABLE);
			TIM_Cmd(TIM4, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_Init(GPIOD,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PD14)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);		
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);		
			TIM_OC3Init(TIM4, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM4, ENABLE);
			TIM_Cmd(TIM4, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			GPIO_Init(GPIOD, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
			TIM_OC3Init(TIM4, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM4, ENABLE);
			TIM_Cmd(TIM4, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			GPIO_Init(GPIOD,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PD15)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);		
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);		
			TIM_OC4Init(TIM4, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM4, ENABLE);
			TIM_Cmd(TIM4, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
			GPIO_Init(GPIOD, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
			TIM_OC4Init(TIM4, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM4, ENABLE);
			TIM_Cmd(TIM4, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
			GPIO_Init(GPIOD,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PH10)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_TIM5);		
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);		
			TIM_OC1Init(TIM5, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM5, ENABLE);
			TIM_Cmd(TIM5, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOH, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_TIM5);
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM5, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM5, ENABLE);
			TIM_Cmd(TIM5, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOH,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PH11)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_TIM5);		
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);		
			TIM_OC2Init(TIM5, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM5, ENABLE);
			TIM_Cmd(TIM5, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			GPIO_Init(GPIOH, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_TIM5);
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
			TIM_OC2Init(TIM5, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM5, ENABLE);
			TIM_Cmd(TIM5, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			GPIO_Init(GPIOH,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PH12)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_TIM5);		
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);		
			TIM_OC3Init(TIM5, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM5, ENABLE);
			TIM_Cmd(TIM5, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_Init(GPIOH, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_TIM5);
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
			TIM_OC3Init(TIM5, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM5, ENABLE);
			TIM_Cmd(TIM5, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_Init(GPIOH,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PI0)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource0, GPIO_AF_TIM5);		
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);		
			TIM_OC4Init(TIM5, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM5, ENABLE);
			TIM_Cmd(TIM5, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOI, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource0, GPIO_AF_TIM5);
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
			TIM_OC4Init(TIM5, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM5, ENABLE);
			TIM_Cmd(TIM5, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PA0)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);		
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		
			TIM_OC1Init(TIM2, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM2, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOA, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
			TIM_OC1Init(TIM2, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM2, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOA,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PA1)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);		
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		
			TIM_OC2Init(TIM2, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM2, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_Init(GPIOA, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
			TIM_OC2Init(TIM2, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM2, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_Init(GPIOA,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PA2)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);		
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		
			TIM_OC3Init(TIM2, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM2, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOA, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
			TIM_OC3Init(TIM2, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM2, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOA,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PA3)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);		
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		
			TIM_OC4Init(TIM2, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM2, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOA, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
			TIM_OC4Init(TIM2, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM2, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOA,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PI5)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_TIM8);	
			TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
			TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
			TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
			TIM_OC1Init(TIM8, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
			TIM_CtrlPWMOutputs(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);
//			TIM8_Config();
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_Init(GPIOI, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_TIM8);
			TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OC1Init(TIM8, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
			TIM_CtrlPWMOutputs(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PI6)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_TIM8);
			TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;			
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			
			TIM_OC2Init(TIM8, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
			TIM_CtrlPWMOutputs(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			GPIO_Init(GPIOI, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_TIM8);
			TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OC2Init(TIM8, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PI7)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_TIM8);	
			TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;			
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			
			TIM_OC3Init(TIM8, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM8, ENABLE);
			TIM_CtrlPWMOutputs(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_Init(GPIOI, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_TIM8);
			TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
			
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OC3Init(TIM8, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM8, ENABLE);
			TIM_CtrlPWMOutputs(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
	}
	else if(PWM_Channel == PI2)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
		if(PWM_Mode == Mode_PWM_Up)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_TIM8);	
			TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);	
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			
			TIM_OC4Init(TIM8, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM8, ENABLE);
			TIM_CtrlPWMOutputs(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);
		}
		else if(PWM_Mode == Mode_PWM_Down)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOI, &GPIO_InitStructure);				
			GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_TIM8);
			TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OC4Init(TIM8, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
			TIM_ARRPreloadConfig(TIM8, ENABLE);
			TIM_CtrlPWMOutputs(TIM8, ENABLE);
			TIM_Cmd(TIM8, ENABLE);
		}
		else if(PWM_Mode == Mode_In)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
		else if(PWM_Mode == Mode_Out)
		{
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
	}
}

void PWM_Motor_Set(PWM_Motor_Channel_t PWM_Motor_Channel,uint16_t psc,uint16_t pwm)
{	
	uint16_t  TIM_Prescaler;
	switch(PWM_Motor_Channel)
	{
		case 1:
		{
			TIM_Prescaler = ((180000000/107)/psc -1);
			TIM1->PSC = TIM_Prescaler;
			TIM_SetCompare1(TIM1, pwm);
			break;
		}
		case 2:
		{
			TIM_Prescaler = ((180000000/107)/psc -1);
			TIM1->PSC = TIM_Prescaler;
			TIM_SetCompare2(TIM1, pwm);
			break;
		}
		case 3:
		{
			TIM_Prescaler = ((180000000/107)/psc -1);
			TIM1->PSC = TIM_Prescaler;
			TIM_SetCompare3(TIM1, pwm);	
			break;
		}
		case 4:
		{
			TIM_Prescaler = ((180000000/107)/psc -1);
			TIM1->PSC = TIM_Prescaler;
			TIM_SetCompare4(TIM1, pwm);
			break;
		}
	}
}

int PWM_Motor_Scan(PWM_Motor_Channel_t PWM_Motor_Channel)
{
	switch(PWM_Motor_Channel)
	{
		case 1:
		{
			return PWM_PA8_READ;
		}
		case 2:
		{
			return PWM_PA9_READ;
		}
		case 3:
		{
			return PWM_PE13_READ;	
		}
		case 4:
		{
			return PWM_PE14_READ;
		}
		case 5:
		{
			return 0;
		}
	}
		return 0;
}

void PWM_Motor_Out_Set(PWM_Motor_Channel_t PWM_Motor_Channel,PWM_Out_t PWM_Out)
{
	switch(PWM_Motor_Channel)
	{
		case 1:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PA8_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PA8_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PA8_TOGGLE();
			}
			break;
		}
		case 2:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PA9_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PA9_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PA9_TOGGLE();
			}
			break;
		}
		case 3:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PE13_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PE13_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PE13_TOGGLE();
			}
			break;
		}
		case 4:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PE14_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PE14_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PE14_TOGGLE();
			}
			break;
		}
	}
}


void PWM_Set(PWM_Channel_t PWM_Channel,uint16_t psc,uint16_t pwm)
{	
	uint16_t  TIM_Prescaler;
	switch(PWM_Channel)
	{
		case 1:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM4->PSC = TIM_Prescaler;
			TIM_SetCompare1(TIM4, pwm);
			break;
		}
		case 2:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM4->PSC = TIM_Prescaler;
			TIM_SetCompare2(TIM4, pwm);
			break;
		}
		case 3:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM4->PSC = TIM_Prescaler;
			TIM_SetCompare3(TIM4, pwm);	
			break;
		}
		case 4:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM4->PSC = TIM_Prescaler;
			TIM_SetCompare4(TIM4, pwm);
			break;
		}
		case 5:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM5->PSC = TIM_Prescaler;
			TIM_SetCompare1(TIM5, pwm);
			break;
		}
		case 6:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM5->PSC = TIM_Prescaler;
			TIM_SetCompare2(TIM5, pwm);
			break;
		}
		case 7:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM5->PSC = TIM_Prescaler;
			TIM_SetCompare3(TIM5, pwm);
			break;
		}
		case 8:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM5->PSC = TIM_Prescaler;
			TIM_SetCompare4(TIM5, pwm);
			break;
		}
		case 9:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM2->PSC = TIM_Prescaler;
			TIM_SetCompare1(TIM2, pwm);
			break;
		}
		case 10:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM2->PSC = TIM_Prescaler;
			TIM_SetCompare2(TIM2, pwm);
			break;
		}
		case 11:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM2->PSC = TIM_Prescaler;
			TIM_SetCompare3(TIM2, pwm);
			break;
		}
		case 12:
		{
			TIM_Prescaler = ((90000000/107)/psc -1);
			TIM2->PSC = TIM_Prescaler;
			TIM_SetCompare4(TIM2, pwm);
			break;
		}
		case 13:
		{
			TIM_Prescaler = ((180000000/107)/psc -1);
			TIM8->PSC = TIM_Prescaler;
			TIM_SetCompare1(TIM8, pwm);
			break;
		}
		case 14:
		{
			TIM_Prescaler = ((180000000/107)/psc -1);
			TIM8->PSC = TIM_Prescaler;
			TIM_SetCompare2(TIM8, pwm);
			break;
		}
		case 15:
		{
			TIM_Prescaler = ((180000000/107)/psc -1);
			TIM8->PSC = TIM_Prescaler;
			TIM_SetCompare3(TIM8, pwm);
			break;
		}
		case 16:
		{
			TIM_Prescaler = ((180000000/107)/psc -1);
			TIM8->PSC = TIM_Prescaler;
			TIM_SetCompare4(TIM8, pwm);
			break;
		}
		case 17:
		{
			break;
		}
	}
}

int PWM_Io_Scan(PWM_Channel_t PWM_Channel)
{
	switch(PWM_Channel)
	{
		case 1:
		{
			return PWM_PD12_READ;
		}
		case 2:
		{
			return PWM_PD13_READ;
		}
		case 3:
		{
			return PWM_PD14_READ;	
		}
		case 4:
		{
			return PWM_PD15_READ;
		}
		case 5:
		{
			return PWM_PH10_READ;
		}
		case 6:
		{
			return PWM_PH11_READ;
		}
		case 7:
		{
			return PWM_PH12_READ;
		}
		case 8:
		{
			return PWM_PI0_READ;
		}
		case 9:
		{
			return PWM_PA0_READ;
		}
		case 10:
		{
			return PWM_PA1_READ;
		}
		case 11:
		{
			return PWM_PA2_READ;
		}
		case 12:
		{
			return PWM_PA3_READ;
		}
		case 13:
		{
			return PWM_PI5_READ;
		}
		case 14:
		{
			return PWM_PI6_READ;
		}
		case 15:
		{
			return PWM_PI7_READ;
		}
		case 16:
		{
			return PWM_PI2_READ;
		}
		case 17:
		{
			return 0;
		}
	}
	return 0;
}

void PWM_Out_Set(PWM_Channel_t PWM_Channel,PWM_Out_t PWM_Out)
{
	switch(PWM_Channel)
	{
		case 1:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PD12_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PD12_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PD12_TOGGLE();
			}
			break;
		}
		case 2:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PD13_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PD13_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PD13_TOGGLE();
			}
			break;
		}
		case 3:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PD14_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PD14_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PD14_TOGGLE();
			}
			break;
		}
		case 4:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PD15_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PD15_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PD15_TOGGLE();
			}
			break;
		}
		case 5:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PH10_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PH10_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PH10_TOGGLE();
			}
			break;
		}
		case 6:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PH11_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PH11_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PH11_TOGGLE();
			}
			break;
		}
		case 7:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PH12_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PH12_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PH12_TOGGLE();
			}
			break;
		}
		case 8:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PI0_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PI0_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PI0_TOGGLE();
			}
			break;
		}
		case 9:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PA0_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PA0_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PA0_TOGGLE();
			}
			break;
		}
		case 10:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PA1_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PA1_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PA1_TOGGLE();
			}
			break;
		}
		case 11:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PA2_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PA2_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PA2_TOGGLE();
			}
			break;
		}
		case 12:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PA3_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PA3_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PA3_TOGGLE();
			}
			break;
		}
		case 13:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PI5_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PI5_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PI5_TOGGLE();
			}
			break;
		}
		case 14:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PI6_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PI6_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PI6_TOGGLE();
			}
			break;
		}
		case 15:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PI7_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PI7_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PI7_TOGGLE();
			}
			break;
		}
		case 16:
		{if(PWM_Out == PWM_IO_High)
			{
				PWM_PI2_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PI2_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PI2_TOGGLE();
			}
			break;
		}
		case 17:
		{
			if(PWM_Out == PWM_IO_High)
			{
				PWM_PD12_HIGH();
				PWM_PD13_HIGH();
				PWM_PD14_HIGH();
				PWM_PD15_HIGH();
				PWM_PH10_HIGH();
				PWM_PH11_HIGH();
				PWM_PH12_HIGH();
				PWM_PI0_HIGH();
				PWM_PA0_HIGH();
				PWM_PA1_HIGH();
				PWM_PA2_HIGH();
				PWM_PA3_HIGH();
				PWM_PI5_HIGH();
				PWM_PI6_HIGH();
				PWM_PI7_HIGH();
				PWM_PI2_HIGH();
			}
			else if(PWM_Out == PWM_IO_Low)
			{
				PWM_PD12_LOW();
				PWM_PD13_LOW();
				PWM_PD14_LOW();
				PWM_PD15_LOW();
				PWM_PH10_LOW();
				PWM_PH11_LOW();
				PWM_PH12_LOW();
				PWM_PI0_LOW();
				PWM_PA0_LOW();
				PWM_PA1_LOW();
				PWM_PA2_LOW();
				PWM_PA3_LOW();
				PWM_PI5_LOW();
				PWM_PI6_LOW();
				PWM_PI7_LOW();
				PWM_PI2_LOW();
			}
			else if(PWM_Out == PWM_IO_Toggle)
			{
				PWM_PD12_TOGGLE();
				PWM_PD13_TOGGLE();
				PWM_PD14_TOGGLE();
				PWM_PD15_TOGGLE();
				PWM_PH10_TOGGLE();
				PWM_PH11_TOGGLE();
				PWM_PH12_TOGGLE();
				PWM_PI0_TOGGLE();
				PWM_PA0_TOGGLE();
				PWM_PA1_TOGGLE();
				PWM_PA2_TOGGLE();
				PWM_PA3_TOGGLE();
				PWM_PI5_TOGGLE();
				PWM_PI6_TOGGLE();
				PWM_PI7_TOGGLE();
				PWM_PI2_TOGGLE();
			}
			break;
		}
	}
}

void TIM1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* GPIOA, GPIOE clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);
  
  /* GPIOC Configuration: TIM1 CH1 (PA8), TIM1 CH2 (PA9), TIM1 CH3 (PE13) and TIM1 CH4 (PE14) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Connect TIM3 pins to AF */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1); 
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
}

void TIM8_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM8 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

  /* GPIOI clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* Connect TIM8 pins to AF */  
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_TIM8); 
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_TIM8); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	
  TIM_OC1Init(TIM8, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM8, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM8, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
  /* TIM8 enable counter */
  TIM_Cmd(TIM8, ENABLE);
}



void TIM2_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM2 pins to AF */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}




void TIM4_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect TIM4 pins to AF */  
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4); 
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);
}



void TIM5_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM5 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  /* GPIOH, GPIOI clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* Connect TIM5 pins to AF */  
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_TIM5); 
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource0, GPIO_AF_TIM5); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM5, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM5, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM5, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM5, ENABLE);
  /* TIM5 enable counter */
  TIM_Cmd(TIM5, ENABLE);
}



void TIM1_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* GPIOA, GPIOE clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);
  
  /* GPIOC Configuration: TIM1 CH1 (PA8), TIM1 CH2 (PA9), TIM1 CH3 (PE13) and TIM1 CH4 (PE14) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Connect TIM3 pins to AF */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1); 
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_Period;
  TIM_TimeBaseStructure.TIM_Prescaler = PWM_Prescaler;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	if(PWM_CounterMode == PWM_CounterMode_Up)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	else if(PWM_CounterMode == PWM_CounterMode_Down)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
	if(PWM_OCMode == PWMO_OCMode_PWM1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	else if(PWM_OCMode == PWM_OCMode_PWM2)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;
	
	if(PWM_OCPolarity == PWM_OCPolarity_High)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else if(PWM_OCPolarity == PWM_OCPolarity_Low)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
}

void TIM8_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM8 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

  /* GPIOI clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* Connect TIM8 pins to AF */  
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_TIM8); 
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_TIM8); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_Period;
  TIM_TimeBaseStructure.TIM_Prescaler = PWM_Prescaler;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
  if(PWM_CounterMode == PWM_CounterMode_Up)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	else if(PWM_CounterMode == PWM_CounterMode_Down)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  if(PWM_OCMode == PWMO_OCMode_PWM1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	else if(PWM_OCMode == PWM_OCMode_PWM2)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;
  
	if(PWM_OCPolarity == PWM_OCPolarity_High)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else if(PWM_OCPolarity == PWM_OCPolarity_Low)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	
  TIM_OC1Init(TIM8, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC2Init(TIM8, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC4Init(TIM8, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
  /* TIM8 enable counter */
  TIM_Cmd(TIM8, ENABLE);
}



void TIM2_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM2 pins to AF */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_Period;
  TIM_TimeBaseStructure.TIM_Prescaler = PWM_Prescaler;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
  if(PWM_CounterMode == PWM_CounterMode_Up)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	else if(PWM_CounterMode == PWM_CounterMode_Down)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
	
  if(PWM_OCMode == PWMO_OCMode_PWM1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	else if(PWM_OCMode == PWM_OCMode_PWM2)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;
  
	if(PWM_OCPolarity == PWM_OCPolarity_High)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else if(PWM_OCPolarity == PWM_OCPolarity_Low)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}




void TIM4_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect TIM4 pins to AF */  
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4); 
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_Period;
  TIM_TimeBaseStructure.TIM_Prescaler = PWM_Prescaler;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  
	if(PWM_CounterMode == PWM_CounterMode_Up)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	else if(PWM_CounterMode == PWM_CounterMode_Down)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
	if(PWM_OCMode == PWMO_OCMode_PWM1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	else if(PWM_OCMode == PWM_OCMode_PWM2)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  
	if(PWM_OCPolarity == PWM_OCPolarity_High)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else if(PWM_OCPolarity == PWM_OCPolarity_Low)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;
	
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);
}



void TIM5_Config(int PWM_Period,int PWM_Prescaler,int PWM_Pluse,\
	PWM_CounterMode_t PWM_CounterMode,PWM_OCMode_t PWM_OCMode,PWM_OCPolarity_t PWM_OCPolarity)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM5 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  /* GPIOH, GPIOI clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* Connect TIM5 pins to AF */  
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_TIM5); 
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource0, GPIO_AF_TIM5); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_Period;
  TIM_TimeBaseStructure.TIM_Prescaler = PWM_Prescaler;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  
	if(PWM_CounterMode == PWM_CounterMode_Up)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	else if(PWM_CounterMode == PWM_CounterMode_Down)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  if(PWM_OCMode == PWMO_OCMode_PWM1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	else if(PWM_OCMode == PWM_OCMode_PWM2)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	
  if(PWM_OCPolarity == PWM_OCPolarity_High)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else if(PWM_OCPolarity == PWM_OCPolarity_Low)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;
	
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC2Init(TIM5, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC3Init(TIM5, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_Pluse;

  TIM_OC4Init(TIM5, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM5, ENABLE);
  /* TIM5 enable counter */
  TIM_Cmd(TIM5, ENABLE);
}


static void TIM1_Down_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* GPIOA, GPIOE clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);
  
  /* GPIOC Configuration: TIM1 CH1 (PA8), TIM1 CH2 (PA9), TIM1 CH3 (PE13) and TIM1 CH4 (PE14) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Connect TIM3 pins to AF */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1); 
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
}

static void TIM8_Down_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM8 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

  /* GPIOI clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* Connect TIM8 pins to AF */  
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_TIM8); 
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_TIM8); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB2;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	
  TIM_OC1Init(TIM8, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM8, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM8, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
  /* TIM8 enable counter */
  TIM_Cmd(TIM8, ENABLE);
}



static void TIM2_Down_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM2 pins to AF */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}




static void TIM4_Down_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect TIM4 pins to AF */  
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4); 
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);
}



static void TIM5_Down_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM5 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  /* GPIOH, GPIOI clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* Connect TIM5 pins to AF */  
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_TIM5); 
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource0, GPIO_AF_TIM5); 
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RESOLUTION;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC_APB1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC2Init(TIM5, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC3Init(TIM5, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;

  TIM_OC4Init(TIM5, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM5, ENABLE);
  /* TIM5 enable counter */
  TIM_Cmd(TIM5, ENABLE);
}



