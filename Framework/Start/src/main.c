/**
  ******************************************************************************
  * @file    main.c
  * @author  RoboMentor,  site:www.robomentor.cn
  * @version V1.9.6
  ******************************************************************************
	* @describe �����������
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
	//ʱ�� ��ʼ��
	delay_init(configTICK_RATE_HZ);
	
#if RoboMentor_Board_Mission == 1	 
	//����USB ��ʼ��
	usb_Init();
	
	//LED�� ��ʼ��
	Led_Init();
	
	//������ ��ʼ��
	Buzzer_Init();
	RoboMentor_Board_Start_Music();
	
	//24v��Դ ��ʼ��
	Power_24V_Init();
	
	//CAN1 ��ʼ��
	CAN1_Init();
	
	//CAN2 ��ʼ��
	CAN2_Init();
	
	//USART ��ʼ��
	#if DJI_Remote_Control == 0
	USART1_Config(115200,Usart_TxRx,Usart_Parity_No);
	#endif
	USART2_Config(115200,Usart_TxRx,Usart_Parity_No);
	USART3_Config(115200,Usart_TxRx,Usart_Parity_No);
	USART6_Config(115200,Usart_TxRx,Usart_Parity_No);
	
	//UART ��ʼ��
	UART7_Config(115200,Usart_TxRx,Usart_Parity_No);
	UART8_Config(115200,Usart_TxRx,Usart_Parity_No);
	
	//5v��Դ ��ʼ��
	Power_5v_Init();
	
	//��ʱ�� ��ʼ��
	TIM1_Config(PWM_RESOLUTION,TIM_PSC_APB2,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	TIM8_Config(PWM_RESOLUTION,TIM_PSC_APB2,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	TIM2_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	TIM4_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	TIM5_Config(PWM_RESOLUTION,TIM_PSC_APB1,SERVO_DEFAULT_DUTY,PWM_CounterMode_Down,PWMO_OCMode_PWM1,PWM_OCPolarity_High);
	
	//Mpu�����ǳ�ʼ��
	IMU_Init();
	
	//ADC ��ʼ��
	Adc_Init();
#endif

#if DJI_Remote_Control == 1
	DJI_Remote_Control_Init();
#endif

	//freertos�����ʼ��
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
