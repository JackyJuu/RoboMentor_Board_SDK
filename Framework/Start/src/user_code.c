/**
  ******************************************************************************
  * @file    user_code.c
  * @author  JackyJuu,  site:www.robomentor.cn
	* @Note 		You can include there ".h" files.
							#include "djirc.h"
							#include "led.h"
							#include "pwm.h"
							#include "buzzer.h"
							#include "uart.h"
							#include "io.h"
							#include "key.h"
							#include "sd.h"
							#include "power.h"
							#include "can.h"	
							#include "adc.h"
							#include "imu.h"
							#include "usb_uart.h"
							#include "djirc.h"
							#include "flash.h"
							#include "pid.h"
  * @version 	V1.9.6
	* @data			V1.9.6:新增PID控制代码""pid.c"和"pid.h"
										 与中断相关内容"IRQHandler.c"一起放在了Service文件夹中
  ******************************************************************************
	* @describe 用户代码编写处
*/

#include "user_code.h"
#include "led.h"
#include "pwm.h"
#include "buzzer.h"
#include "uart.h"
#include "io.h"
#include "key.h"
#include "sd.h"
#include "djirc.h"
#include "power.h"
#include "can.h"
#include "adc.h"
#include "imu.h"
#include "usb_uart.h"
#include "djirc.h"
#include "flash.h"
#include "pid.h"

void user1_main(void)
{

	while(1)
	{

		delay_ms(1);	
	}
}


void user2_main(void)
{

	while(1)
	{

		delay_ms(1);
	}
}

void user3_main(void)
{
	while(1)
	{
		
		delay_ms(1);
	}
}

void user4_main(void)
{
	while(1)
	{
		
		delay_ms(1);
	}
}

void user5_main(void)
{
	while(1)
	{
		
		delay_ms(1);
	}
}



	
