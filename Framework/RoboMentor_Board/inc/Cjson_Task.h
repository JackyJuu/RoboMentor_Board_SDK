#ifndef CJSON_TASK_H
#define CJSON_TASK_H

#include "stm32fxxx_it.h"

typedef struct
{
    char* type;
    char* channel;
		char* status;
}LED_CONTROL_TEST;

/******LED_JSON******/
typedef struct
{	
	char* type;//操作类型，string类型数据，可用值：WRITE-LED
  char* channel;//通道ID，string类型数据，可用参数：GREEN、RED、BLUE
	char* status;//开关状态，string类型数据，可用参数：OFF、ON、TOGGLE
}LED_JSON_t;


/******CAN_JSON******/

//读取数据
typedef struct
{	
	char* type;//操作类型，string类型数据，可用值：READ-CAN1、READ-CAN2
	char* stdid;//CAN通讯电机标识符，string类型十六进制数据，具体可查阅电机电调手册获取，例如：0x200	
}CAN_READ_JSON_t;

//写入数据
typedef struct
{	
	char* type;//string类型数据，可用值：WRITE-CAN1、WRITE-CAN2
	char* stdid;//CAN通讯标识符，string类型十六进制数据，具体可查阅电机电调手册获取，例如：0x200
	int motor;//电机ID，int类型数据，例如：2
	int control;//电机控制值，int类型数据，需参考使用电机的控制值范围
}CAN_WRITE_JSON_t;

//重置状态
typedef struct
{	
	char* type;//string类型数据，可用值：WRITE-CAN1、WRITE-CAN2
	char* stdid;//CAN通讯标识符，string类型十六进制数据，具体可查阅电机电调手册获取，例如：0x200
}CAN_RESET_JSON_t;

//读取后的返回数据
typedef struct
{	
	char* type;//当前读取数据类型，string类型数据
	int stdid;//CAN通讯标识符，int类型十六进制数据，具体可查阅电机电调手册获取，例如：0x200
	int speed;//当前转速，int类型数据
	int current;//当前电流，int类型数据
	float* temperature;//当前温度，float类型数据
	float* angle;//当前角度，float类型数据	
}CAN_REBACK_JSON_t;

//CAN数据交互
typedef struct
{
	CAN_READ_JSON_t CAN_READ_JSON;//CAN读取数据
	CAN_WRITE_JSON_t CAN_WRITE_JSON;//CAN写入数据
	CAN_RESET_JSON_t CAN_RESET_JSON;//重置状态
	CAN_REBACK_JSON_t CAN_REBACK_JSON;//CAN读取后的返回数据
}CAN_JSON_t;

/******PWM_JSON******/
//写入数据
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：WRITE-PWM
	int channel;//通道ID，int类型数据，例如：1
	int width;//脉宽数据，int类型数据，例如：2000
	float rate;//频率，float类型数据，例如：100
}PWM_WRITE_JSON_t;

//读取数据
typedef struct
{
	char* type;//string类型数据，可用值：READ-PWM
	int channel;//通道ID，int类型数据，例如：1
}PWM_READ_JSON_t;

//读取后的返回数据
typedef struct
{
	char* type;
	int channel;
	float* voltage;
}PWM_REBACK_JSON_t;

//PWM数据交互
typedef struct
{
	PWM_WRITE_JSON_t PWM_WRITE_JSON;//PWM写入数据
	PWM_READ_JSON_t PWM_READ_JSON;//PWM读取数据
	PWM_REBACK_JSON_t PWM_REBACK_JSON;//PWM读取后的返回数据
}PWM_JSON_t;

/******UART_JSON******/
//写入数据
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：WRITE-UART
	int channel;//通道ID，int类型数据，例如：1
	char* data;//自定义数据，string类型数据，根据自己的情况约定数据
}UART_WRITE_JSON_t;

//读取数据
typedef struct
{
	char* type;//string类型数据，可用值：READ-UART
	int channel;//通道ID，int类型数据，例如：1
	char* data_last_t;
}UART_READ_JSON_t;

//读取返回后的数据
typedef struct
{
	char* type;//当前读取数据类型，string类型数据
	int channel;//当前通道ID，int类型数据
	char* data;//自定义数据，string类型数据
}UART_REBACK_JSON_t;

//UART串口数据交互
typedef struct
{
	UART_WRITE_JSON_t UART_WRITE_JSON;
	UART_READ_JSON_t UART_READ_JSON;
	UART_REBACK_JSON_t UART_REBACK_JSON;
}UART_JSON_t;

/******IMU_JSON******/
//读取数据
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：READ-IMU
}IMU_READ_JSON_t;

//读取后的返回数据
typedef struct
{
	char* type;//当前读取数据类型，string类型数据
	float* X;//当前角度x数据，float类型数据
	float* Y;//当前角度y数据，float类型数据
	float* Z;//当前角度z数据，float类型数据
	float* temperature;//当前温度，float类型数据
	float* pressure;//当前气压，float类型数据
}IMU_REBACK_JSON_t;

//IMU数据交互
typedef struct
{
	IMU_READ_JSON_t IMU_READ_JSON;
	IMU_REBACK_JSON_t IMU_REBACK_JSON;
}IMU_JSON_t;

/******POWER_5V/24V_JSON******/
//5V电源写入数据
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：WRITE-POWER5
	int channel;//通道ID，int类型数据，例如：1
	char* status;//开关状态，string类型数据，可用参数：OFF、ON
}POWER_5V_JSON_t;

//24V电源写入数据
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：WRITE-POWER24
	int channel;//通道ID，int类型数据，例如：1
	char* status;//开关状态，string类型数据，可用参数：OFF、ON
}POWER_24V_JSON_t;

/******POWER_LIMIT_JSON******/
//读取数据
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：READ-POWER
}POWER_READ_JSON_t;

//读取后的返回数据
typedef struct
{
	char* type;//当前读取数据类型，string类型数据
	float* voltage;//当前电压数据，float类型数据
}POWER_REBACK_JSON_t;

//电源电量数据交互
typedef struct
{
	POWER_READ_JSON_t POWER_READ_JSON;
	POWER_REBACK_JSON_t POWER_REBACK_JSON;
}POWER_LIMIT_JSON_t;

/******BUZZER_JSON******/
//蜂鸣器写入数据
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：WRITE-BUZZER
	int tone;//音调，string类型数据
}BUZZER_WIRTE_JSON_t;

//选择乐谱
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：WRITE-SONG
	char* music;//选择乐谱，string类型数据，可用值：”小星星“,“千与千寻”
	int speed;//播放速度，int类型数据，可用值：1-9，正常5
}BUZZER_SONG_JSON_t;

//停止播放
typedef struct
{
	char* type;//操作类型，string类型数据，可用值：STOP-BUZZER
}BUZZER_STOP_JSON_t;

//蜂鸣器数据交互
typedef struct
{
	BUZZER_WIRTE_JSON_t BUZZER_WIRTE_JSON;
	BUZZER_SONG_JSON_t BUZZER_SONG_JSON;
	BUZZER_STOP_JSON_t BUZZER_STOP_JSON;
}BUZZER_JSON_t;

/******TF_CARD_JSON******/
//写入数据
typedef struct
{
	char* type;
	char* file;
	char* data;
}TF_CARD_WRITE_JSON_t;

//追加数据
typedef struct
{
	char* type;
	char* file;
	char* data;
}TF_CARD_ADD_JSON_t;

//读取数据
typedef struct
{
	char* type;
	char* file;
}TF_CARD_READ_JSON_t;

//删除数据
typedef struct
{
	char* type;
	char* file;
}TF_CARD_DELETE_JSON_t;

//读取后的返回数据
typedef struct
{
	char* type;
	char* file;
	char* data;
}TF_CARD_REBACK_JSON_t;

//TF卡数据交互
typedef struct
{
	TF_CARD_WRITE_JSON_t TF_CARD_WRITE_JSON;
	TF_CARD_ADD_JSON_t TF_CARD_ADD_JSON;
	TF_CARD_READ_JSON_t TF_CARD_READ_JSON;
	TF_CARD_DELETE_JSON_t TF_CARD_DELETE_JSON;
	TF_CARD_REBACK_JSON_t TF_CARD_REBACK_JSON;
}TF_CARD_JSON_t;

/******ALL_JSON******/
//所有json数据交互结构体
typedef struct
{
	char* type;
	LED_JSON_t LED_JSON;
	CAN_JSON_t CAN_JSON;
	PWM_JSON_t PWM_JSON;
	UART_JSON_t UART_JSON;
	IMU_JSON_t IMU_JSON;
	POWER_5V_JSON_t POWER_5V_JSON;
	POWER_24V_JSON_t POWER_24V_JSON;
	POWER_LIMIT_JSON_t POWER_LIMIT_JSON;
	BUZZER_JSON_t BUZZER_JSON;
	TF_CARD_JSON_t TF_CARD_JSON;
}ALL_JSON_t;


extern void error_text(int num);
extern void error_text_print(void);
extern void cjson_task(void *pvParameters);
extern void data_clean(uint8_t* data);
extern void data_clean_len(int16_t* data,int len);
extern void data_change(uint8_t* data_in,uint8_t* data_out);

#endif
