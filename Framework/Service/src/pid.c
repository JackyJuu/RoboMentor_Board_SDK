/**
  ******************************************************************************
  * @file    pid.c
  * @author  JackyJuu,  site:www.robomentor.cn
	* @Note 	 pid相关控制函数
  * @version V1.9.6
  ******************************************************************************
	* @describe PID相关函数
*/
#include "pid.h"

//PID限制最大值函数
void PID_limit(float *a, float PID_MAX)
{
    if(*a > PID_MAX)
        *a = PID_MAX;
    if(*a < -PID_MAX)
        *a = -PID_MAX;
}

//PID限制最小值函数
void PID_limitmin(float *a, float PID_MIN)
{
		if(*a < PID_MIN && *a > 0)
        *a = PID_MIN;
    if(*a > -PID_MIN && *a < 0)
        *a = -PID_MIN;
}

//PID限幅函数
float xianfu(float a,float max)
{
	if(a > 50000)
			a=a-max;
	if(a < 50000)
			a=max-a;
 return a;
}

//PID绝对值函数
void PID_juedui(float *a)
{
		if(*a > 0)
        *a = *a;
    if(*a < 0)
        *a = -*a;
}

//PID初始化
void pid_init(PID*pid,float p,float i,float d,int maxout,int imaxout,int mode)
{
	pid->kp=p;
	pid->ki=i;
	pid->kd =d;
	pid->pout =0;
	pid->iout =0;
	pid->dout =0;
	pid->Last_error =0;
	pid->Last_Last_error =0;
	pid->now_error =0;
	pid->sum_of_error =0;
	pid->pid_mode =mode;//1为位置环PID，2为增量式PID
	pid->MaxOutput =maxout;//PID限幅
	pid->IntegralLimit=imaxout;	
	pid->plus =0;
	pid->plus_out =0;
	pid->last_plus_out =0;
}


//PID函数
float pid_calc(PID*pid, float now, float set)
	{
		int flag = 1;
    pid->now = now;
    pid->set = set;

    if(pid->now  > 50000)
			pid->now  = pid->now -65533;
		pid->now_error = flag*pid->set - pid->now;	//set - measure
		if(pid->now_error < 10  && pid->now_error > -10)
		pid->now_error=0;
    if(pid->pid_mode == 1) //位置环PID
    {
	      pid->pout = pid->kp * pid->now_error;
        pid->iout = pid->ki * pid->sum_of_error;
        pid->dout = pid->kd * (pid->now_error - pid->Last_error );
				pid->sum_of_error+=pid->now_error;	
				PID_limit(&(pid->sum_of_error), 20000);
				PID_limit(&(pid->iout), pid->IntegralLimit);
        pid->out = pid->pout + pid->iout + pid->dout;
        PID_limit(&(pid->out), pid->MaxOutput);
    }	
		
    else if(pid->pid_mode == 2)//增量式PID
    {
        pid->pout = pid->kp * (pid->now_error - pid->Last_error);
        pid->iout = pid->ki * pid->now_error;
        pid->dout = pid->kd * (pid->now_error - 2*pid->Last_error + pid->Last_Last_error);        
				PID_limit(&(pid->iout), pid->IntegralLimit);
        pid->plus = pid->pout + pid->iout + pid->dout;
        pid->plus_out = pid->last_plus_out + pid->plus;
			  pid->out = pid->plus_out; 
				PID_limit(&(pid->out), pid->MaxOutput);
        pid->last_plus_out = pid->plus_out;	//update last time
    }
		
    pid->Last_Last_error= pid->Last_error;
    pid->Last_error = pid->now_error;

    return pid->out*flag;
}

