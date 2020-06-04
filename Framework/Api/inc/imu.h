#ifndef __IMU_H__
#define __IMU_H__
#include "stm32f4xx.h"

void IMU_Init(void);
void IMU_Date_Get(float*yaw,float*pitch,float*roll);
void IMU_Tem_Get(float* IMU_Tem);
void Altitude_Data_Get(float* Altitude);

/*
	������ԭʼ���ݻ�ȡ
	IMU_Acce[] = {ax,ay,az};//Ϊ���ٶȵĲ���ֵ
	IMU_Gyro[] = {gx,gy,gz};//Ϊ�����ǵĲ���ֵ
	IMU_Magn[] = {mx,my,mz};//Ϊ�شżƵĲ���ֵ 
*/
void IMU_Old_Data(int16_t* IMU_Acce,int16_t* IMU_Gyro,int16_t* IMU_Magn);


#endif
