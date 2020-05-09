#ifndef ADC_H
#define ADC_H
#include "stm32f4xx.h"

extern void Power_Limit_Init(void);

extern int Power_Detect(void);

int Get_Power_Average(int num);
float Power_Read(int num);

extern void Temperture_Init(void);
extern void Temperature_ADC_Reset(void);

extern int Get_Temperature_Average(int num);
float Temperature_Read(int num);

extern uint16_t Get_Temperature_ADC(uint8_t ch);

#endif
