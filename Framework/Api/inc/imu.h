#ifndef __IMU_H__
#define __IMU_H__
#include "stm32f4xx.h"

void IMU_Init(void);
void IMU_Date_Get(float*yaw,float*pitch,float*roll);
void IMU_Tem_Get(float* IMU_Tem);
void Altitude_Data_Get(float* Altitude);

/*
	陀螺仪原始数据获取
	IMU_Acce[] = {ax,ay,az};//为加速度的测量值
	IMU_Gyro[] = {gx,gy,gz};//为陀螺仪的测量值
	IMU_Magn[] = {mx,my,mz};//为地磁计的测量值 
*/
void IMU_Old_Data(int16_t* IMU_Acce,int16_t* IMU_Gyro,int16_t* IMU_Magn);


#endif
