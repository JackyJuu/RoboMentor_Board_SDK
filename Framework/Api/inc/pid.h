#ifndef _pid_h_
#define _pid_h_

//PID结构体
typedef struct PID
{
	float kp;//kp
	float ki;//ki
	float kd;//kd
	double pout;//k输出
	float iout;//i输出
	float dout;//d输出
	float now_error;			//当前误差
	float Last_error;			//上一次误差
	float Last_Last_error;	//上上次误差
	float sum_of_error;     //历史总误差
	float set;		//设置
	float now;		//当前
	float out;		//输出

	int pid_mode;	//PID模式设置，1为位置环PID，2为增量式PID
 
  float MaxOutput;//PID输出限幅	
	float IntegralLimit;//I输出限幅	
	float plus;		//本次增量值
  float plus_out;	//增量式输出值plus_out = last_plus_out + plus
  float last_plus_out;//上次增量式输出值
}PID;		

//PID限制最大值函数
void PID_limit(float *a, float PID_MAX);

//PID限制最小值函数
void PID_limitmin(float *a, float PID_MIN);

//PID限幅函数
float xianfu(float a,float max);

//PID绝对值函数
void PID_juedui(float *a);

//PID初始化
void pid_init(PID*pid,float p,float i,float d,int maxout,int imaxout,int mode);

//pid参数更新
void pid_change(PID*pid,float p,float i,float d,int maxout,int imaxout,int mode);

//PID函数
float pid_calc(PID*pid, float now, float set);


#endif
