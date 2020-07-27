#include "ad.h"

int tem_read;
int power_read;

void Power_Limit_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		ADC_InitTypeDef ADC_InitStructure;
		DMA_InitTypeDef DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOF, &GPIO_InitStructure);
		
		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC3, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC3,ADC_Channel_9,1,ADC_SampleTime_144Cycles);
	
	ADC_Cmd(ADC3, ENABLE);	//使能指定的ADC3
	 
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC3的软件转换启动功能	
}

void Power_Limit_ADC_Reset(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC3, &ADC_InitStructure);
}

int Power_Detect(void)
{
    int AD_Value;
//		ADC_RegularChannelConfig(ADC3, ADC_Channel_9, 1, ADC_SampleTime_15Cycles);
//    ADC_SoftwareStartConv(ADC3);
    while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));
		{
		
		}
    AD_Value = ADC_GetConversionValue(ADC3);
		return AD_Value;
	
}

int Get_Power_Average(int num)
{
	int pow_sum=0;
	int i;
	for(i=0;i<num;i++)
	{
		pow_sum+=Power_Detect();
	}
	return pow_sum/num;
}

float Power_Read(int num)
{
	float Board_Power;
	power_read=Get_Power_Average(num);
//	Board_Temperature=(float);
//	Board_Temperature=(1.43-Board_Temperature)/0.043+25;
	Board_Power = (float)(power_read*(3.3f/4096.0f));
	Board_Power = (Board_Power/4.7f*104.7f);
//	Board_Power = ((((Board_Power/100)+(Board_Power/4700))*100000)+Board_Power);
	return Board_Power;	
}

void Temperture_Init(void)
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
	
		ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
		ADC_CommonInitStructure.ADC_Mode=ADC_Mode_Independent;
		ADC_CommonInitStructure.ADC_Prescaler=ADC_Prescaler_Div4;
		ADC_CommonInitStructure.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;;
	  ADC_CommonInit(&ADC_CommonInitStructure);
	
		ADC_TempSensorVrefintCmd(ENABLE);//使能温度传感器

		Temperature_ADC_Reset();
	
    ADC_RegularChannelConfig(ADC1,ADC_Channel_18,1,ADC_SampleTime_15Cycles);


		ADC_Cmd(ADC1,ENABLE);	
		ADC_SoftwareStartConv(ADC1);			
}



void Temperature_ADC_Reset(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

}

int Get_Temperature_Average(int num)
{
	int tem_sum=0;
	int i;
	for(i=0;i<num;i++)
	{
		tem_sum+=Get_Temperature_ADC(ADC_Channel_18);;
	}
	return tem_sum/num;
}

float Temperature_Read(int num)
{
	float Board_Temperature;
	Temperature_ADC_Reset();
	tem_read=Get_Temperature_Average(num);
//	Board_Temperature=(float);
//	Board_Temperature=(1.43-Board_Temperature)/0.043+25;
	Board_Temperature = (float)((tem_read*(3300.0f/4096.0f) - 760.0f) / 2.5f + 25.0f);
	return Board_Temperature;	
}

uint16_t Get_Temperature_ADC(uint8_t ch)
{

    ADC_ClearFlag(ADC1,ADC_FLAG_STRT|ADC_FLAG_OVR|ADC_FLAG_EOC);
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_15Cycles);

    ADC_SoftwareStartConv(ADC1);

    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
    {
        ;
    }
    return ADC_GetConversionValue(ADC1);
}