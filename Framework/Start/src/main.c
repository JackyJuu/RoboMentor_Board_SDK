/**
  ******************************************************************************
  * @file    main.c
  * @author  RoboMentor,  site:www.robomentor.cn
  * @version V1.9.6
  ******************************************************************************
	* @describe 程序启动入口
*/
#include "Robomentor_task.h"
#include "stm32fxxx_it.h"
#include "led.h"
#include "imu.h"
#include "djirc.h"
#include "buzzer.h"
#include "power.h"
#include "can.h"
#include "uart.h"
#include "pwm.h"
#include "adc.h"
#include "delay.h"
#include "usb_uart.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "start_task.h"

#include "user_code.h"

int main(void)
 {
	//时钟 初始化
	delay_init(configTICK_RATE_HZ);
	
#if RoboMentor_Board_Mission == 1	 
	//虚拟USB 初始化
	usb_Init();
	
	//LED灯 初始化
	Led_Init();
	
	//蜂鸣器 初始化
	Buzzer_Init();
	RoboMentor_Board_Start_Music();
	
	//24v电源 初始化
	Power_24V_Init();
	
	//CAN1 初始化
	CAN1_Init();
	
	//CAN2 初始化
	CAN2_Init();
	
	//USART 初始化
	#if DJI_Remote_Control == 0
	USART1_Config(115200,Usart_TxRx,Usart_Parity_No);
	#endif
	USART2_Config(115200,Usart_TxRx,Usart_Parity_No);
	USART3_Config(115200,Usart_TxRx,Usart_Parity_No);
	USART6_Config(115200,Usart_TxRx,Usart_Parity_No);
	
	//UART 初始化
	UART7_Config(115200,Usart_TxRx,Usart_Parity_No);
	UART8_Config(115200,Usart_TxRx,Usart_Parity_No);
	
	//5v电源 初始化
	Power_5v_Init();
	
	//定时器 初始化
	TIM1_Config(PWM_RESOLUTION,TIM_PSC_APB2,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	TIM8_Config(PWM_RESOLUTION,TIM_PSC_APB2,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	TIM2_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	TIM4_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	TIM5_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	
	//Mpu陀螺仪初始化
	IMU_Init();
	
	//ADC 初始化
	Adc_Init();
#endif

#if DJI_Remote_Control == 1
	DJI_Remote_Control_Init();
#endif

	//freertos任务初始化
	startTast();
  vTaskStartScheduler();
}

void vApplicationIdleHook( void )
{
	
}

void vApplicationMallocFailedHook( void )
{
	while(1);
}
