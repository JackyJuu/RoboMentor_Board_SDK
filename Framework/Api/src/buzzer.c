#include "delay.h"
#include "buzzer.h"
#include "All_define.h"
#include "Mission_task.h"
#include "task.h"

extern int System_Start;
void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, DISABLE);

    GPIO_PinAFConfig(GPIOH, GPIO_PinSource6, GPIO_AF_TIM12);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOH, &GPIO_InitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC1Init(TIM12, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM12, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = 300 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 900 - 1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM12, &TIM_TimeBaseInitStructure);
    TIM_Cmd(TIM12, ENABLE);
		
}

void RoboMentor_Board_Start_Music(void)
{
		TIM12->PSC = MI_MIDDLE;
	  TIM_SetCompare1(TIM12, 10);
    Delay_ms(100);
		TIM_SetCompare1(TIM12, 300);
		Delay_ms(50);
								
		TIM12->PSC = DO_MIDDLE;
	  TIM_SetCompare1(TIM12, 10);
    Delay_ms(100);
		TIM_SetCompare1(TIM12, 300);
		Delay_ms(50);
								
		TIM12->PSC = MI_MIDDLE;
	  TIM_SetCompare1(TIM12, 10);
    Delay_ms(100);
		TIM_SetCompare1(TIM12, 300);
		Delay_ms(50);
								
		TIM12->PSC = SO_MIDDLE;
	  TIM_SetCompare1(TIM12, 10);
		Delay_ms(500);
		TIM_SetCompare1(TIM12, 300);
		Delay_ms(100);
}

void buzzer_set(uint16_t psc)
{
    TIM12->PSC = psc;
	  TIM_SetCompare1(TIM12, 10);
}

void buzzer_off(void)
{
    TIM_SetCompare1(TIM12, 300);
}

void buzzer_tone(uint16_t psc,int music,int stop)
{
			buzzer_set(psc);
			if(System_Start == 1)
			{
				vTaskDelay(music);
			}
			else if(System_Start == 0)
			{
				Delay_ms(music);
			}
			buzzer_off();
			if(System_Start == 1)
			{
				vTaskDelay(stop);
			}
			else if(System_Start == 0)
			{
				Delay_ms(stop);
			}
			
}

void qianyuqianxun_song(void)
{
	qianyuqianxun_step(1);
	qianyuqianxun_step(2);
	qianyuqianxun_step(3);
	qianyuqianxun_step(4);
	qianyuqianxun_step(5);
	qianyuqianxun_step(6);
	qianyuqianxun_step(7);
	qianyuqianxun_step(8);
	qianyuqianxun_step(9);
	qianyuqianxun_step(10);
	qianyuqianxun_step(11);
	qianyuqianxun_step(12);
	qianyuqianxun_step(13);
	qianyuqianxun_step(14);
	qianyuqianxun_step(15);
	qianyuqianxun_step(16);
	qianyuqianxun_step(17);
	qianyuqianxun_step(18);
	qianyuqianxun_step(19);
	qianyuqianxun_step(20);
	qianyuqianxun_step(21);
	qianyuqianxun_step(22);
	qianyuqianxun_step(23);
	qianyuqianxun_step(24);
	qianyuqianxun_step(25);
	qianyuqianxun_step(26);
	qianyuqianxun_step(27);
	qianyuqianxun_step(28);
	qianyuqianxun_step(29);
	qianyuqianxun_step(30);
	qianyuqianxun_step(31);
	qianyuqianxun_step(32);
	qianyuqianxun_step(33);
	qianyuqianxun_step(34);
	qianyuqianxun_step(35);
	qianyuqianxun_step(36);
	qianyuqianxun_step(37);
	qianyuqianxun_step(38);
	qianyuqianxun_step(39);
	qianyuqianxun_step(40);
	qianyuqianxun_step(41);
	qianyuqianxun_step(42);
	qianyuqianxun_step(43);
	qianyuqianxun_step(44);
	qianyuqianxun_step(45);
	qianyuqianxun_step(46);
	qianyuqianxun_step(47);
	qianyuqianxun_step(48);
	qianyuqianxun_step(49);
	qianyuqianxun_step(50);
	qianyuqianxun_step(51);
	qianyuqianxun_step(52);
	qianyuqianxun_step(53);
	qianyuqianxun_step(54);
	qianyuqianxun_step(55);
	qianyuqianxun_step(56);
	qianyuqianxun_step(57);
	qianyuqianxun_step(58);
	qianyuqianxun_step(59);
	qianyuqianxun_step(60);
	qianyuqianxun_step(61);
}

void little_star_song(void)
{
	little_star_step(1);
	little_star_step(2);
	little_star_step(3);
	little_star_step(4);
	little_star_step(5);
	little_star_step(6);
	little_star_step(7);
	little_star_step(8);
	little_star_step(9);
	little_star_step(10);
	little_star_step(11);
	little_star_step(12);
	little_star_step(13);
	little_star_step(14);
	little_star_step(15);
	little_star_step(16);
	little_star_step(17);
	little_star_step(18);
	little_star_step(19);
	little_star_step(20);
	little_star_step(21);
	little_star_step(22);
	little_star_step(23);
	little_star_step(24);
	little_star_step(25);
	little_star_step(26);
	little_star_step(27);
	little_star_step(28);
	little_star_step(29);
	little_star_step(30);
	little_star_step(31);
	little_star_step(32);
	little_star_step(33);
	little_star_step(34);
	little_star_step(35);
	little_star_step(36);
	little_star_step(37);
	little_star_step(38);
	little_star_step(39);
	little_star_step(40);
	little_star_step(41);
	little_star_step(42);
	little_star_step(43);
	little_star_step(44);
}


void qianyuqianxun_song_step(int step,int misic_tim,int stop_tim)
{
	switch(step)
		{
			case 1:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 2:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 3:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 4:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 5:
			{buzzer_tone(SO_MIDDLE,misic_tim*3,stop_tim);
			break;}
			case 6:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 7:
			{buzzer_tone(RE_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 8:
			{buzzer_tone(SO_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 9:
			{buzzer_tone(RE_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 10:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 11:
			{buzzer_tone(LA_LOW,misic_tim,stop_tim);
			break;}
			case 12:
			{buzzer_tone(MI_MIDDLE,misic_tim*3,stop_tim);
			break;}
			case 13:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 14:
			{buzzer_tone(SI_LOW,misic_tim*4,stop_tim);
			break;}
			case 15:
			{buzzer_tone(SI_LOW,misic_tim,stop_tim);
			break;}
			case 17:
			{buzzer_tone(LA_LOW,misic_tim*2,stop_tim);
			break;}
			case 18:
			{buzzer_tone(SI_LOW,misic_tim*2,stop_tim);
			break;}
			case 19:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 20:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 21:
			{buzzer_tone(FA_LOW,misic_tim*2,stop_tim);
			break;}
			case 22:
			{buzzer_tone(DO_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 23:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 24:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 25:
			{buzzer_tone(FA_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 26:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 27:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 28:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 29:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 30:
			{buzzer_tone(RE_MIDDLE,misic_tim*4,stop_tim);
			break;}
			case 31:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 32:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 34:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 35:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 36:
			{buzzer_tone(SO_MIDDLE,misic_tim*3,stop_tim);
			break;}
			case 37:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 38:
			{buzzer_tone(RE_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 39:
			{buzzer_tone(SO_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 40:
			{buzzer_tone(RE_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 41:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 42:
			{buzzer_tone(LA_LOW,misic_tim,stop_tim);
			break;}
			case 43:
			{buzzer_tone(LA_LOW,misic_tim*2,stop_tim);
			break;}
			case 44:
			{buzzer_tone(SI_LOW,misic_tim,stop_tim);
			break;}
			case 45:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 46:
			{buzzer_tone(FA_LOW,misic_tim*4,stop_tim);
			break;}
			case 47:
			{buzzer_tone(FA_LOW,misic_tim,stop_tim);
			break;}
			case 48:
			{buzzer_tone(LA_LOW,misic_tim*2,stop_tim);
			break;}
			case 49:
			{buzzer_tone(SI_LOW,misic_tim*2,stop_tim);
			break;}
			case 50:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 51:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 52:
			{buzzer_tone(FA_LOW,misic_tim*2,stop_tim);
			break;}
			case 53:
			{buzzer_tone(DO_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 54:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 55:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 56:
			{buzzer_tone(FA_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 57:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 58:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 59:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 60:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 61:
			{buzzer_tone(DO_MIDDLE,misic_tim*6,stop_tim);
			break;}

		}
}

void little_star_song_step(int step,int misic_tim,int stop_tim)
{
			switch(step)
		{
			case 1:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 2:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 3:
			{buzzer_tone(SO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 4:
			{buzzer_tone(SO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 5:
			{buzzer_tone(LA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 6:
			{buzzer_tone(LA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 7:
			{buzzer_tone(SO_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 8:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 9:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 10:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 11:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 12:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 13:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 14:
			{buzzer_tone(DO_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 15:
			{buzzer_tone(SO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 17:
			{buzzer_tone(SO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 18:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 19:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 20:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 21:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 22:
			{buzzer_tone(RE_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 23:
			{buzzer_tone(SO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 24:
			{buzzer_tone(SO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 25:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 26:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 27:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 28:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 29:
			{buzzer_tone(RE_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 30:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 31:
			{buzzer_tone(DO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 32:
			{buzzer_tone(SO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 34:
			{buzzer_tone(SO_MIDDLE,misic_tim,stop_tim);
			break;}
			case 35:
			{buzzer_tone(LA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 36:
			{buzzer_tone(LA_MIDDLE,misic_tim,stop_tim);
			break;}			
			case 37:
			{buzzer_tone(SO_MIDDLE,misic_tim*2,stop_tim);
			break;}
			case 38:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 39:
			{buzzer_tone(FA_MIDDLE,misic_tim,stop_tim);
			break;}
			case 40:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 41:
			{buzzer_tone(MI_MIDDLE,misic_tim,stop_tim);
			break;}
			case 42:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 43:
			{buzzer_tone(RE_MIDDLE,misic_tim,stop_tim);
			break;}
			case 44:
			{buzzer_tone(DO_MIDDLE,misic_tim*2,stop_tim);
			break;}

		}
}