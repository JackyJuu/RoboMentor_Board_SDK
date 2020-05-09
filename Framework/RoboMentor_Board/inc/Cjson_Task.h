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
	char* type;//�������ͣ�string�������ݣ�����ֵ��WRITE-LED
  char* channel;//ͨ��ID��string�������ݣ����ò�����GREEN��RED��BLUE
	char* status;//����״̬��string�������ݣ����ò�����OFF��ON��TOGGLE
}LED_JSON_t;


/******CAN_JSON******/

//��ȡ����
typedef struct
{	
	char* type;//�������ͣ�string�������ݣ�����ֵ��READ-CAN1��READ-CAN2
	char* stdid;//CANͨѶ�����ʶ����string����ʮ���������ݣ�����ɲ��ĵ������ֲ��ȡ�����磺0x200	
}CAN_READ_JSON_t;

//д������
typedef struct
{	
	char* type;//string�������ݣ�����ֵ��WRITE-CAN1��WRITE-CAN2
	char* stdid;//CANͨѶ��ʶ����string����ʮ���������ݣ�����ɲ��ĵ������ֲ��ȡ�����磺0x200
	int motor;//���ID��int�������ݣ����磺2
	int control;//�������ֵ��int�������ݣ���ο�ʹ�õ���Ŀ���ֵ��Χ
}CAN_WRITE_JSON_t;

//����״̬
typedef struct
{	
	char* type;//string�������ݣ�����ֵ��WRITE-CAN1��WRITE-CAN2
	char* stdid;//CANͨѶ��ʶ����string����ʮ���������ݣ�����ɲ��ĵ������ֲ��ȡ�����磺0x200
}CAN_RESET_JSON_t;

//��ȡ��ķ�������
typedef struct
{	
	char* type;//��ǰ��ȡ�������ͣ�string��������
	int stdid;//CANͨѶ��ʶ����int����ʮ���������ݣ�����ɲ��ĵ������ֲ��ȡ�����磺0x200
	int speed;//��ǰת�٣�int��������
	int current;//��ǰ������int��������
	float* temperature;//��ǰ�¶ȣ�float��������
	float* angle;//��ǰ�Ƕȣ�float��������	
}CAN_REBACK_JSON_t;

//CAN���ݽ���
typedef struct
{
	CAN_READ_JSON_t CAN_READ_JSON;//CAN��ȡ����
	CAN_WRITE_JSON_t CAN_WRITE_JSON;//CANд������
	CAN_RESET_JSON_t CAN_RESET_JSON;//����״̬
	CAN_REBACK_JSON_t CAN_REBACK_JSON;//CAN��ȡ��ķ�������
}CAN_JSON_t;

/******PWM_JSON******/
//д������
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��WRITE-PWM
	int channel;//ͨ��ID��int�������ݣ����磺1
	int width;//�������ݣ�int�������ݣ����磺2000
	float rate;//Ƶ�ʣ�float�������ݣ����磺100
}PWM_WRITE_JSON_t;

//��ȡ����
typedef struct
{
	char* type;//string�������ݣ�����ֵ��READ-PWM
	int channel;//ͨ��ID��int�������ݣ����磺1
}PWM_READ_JSON_t;

//��ȡ��ķ�������
typedef struct
{
	char* type;
	int channel;
	float* voltage;
}PWM_REBACK_JSON_t;

//PWM���ݽ���
typedef struct
{
	PWM_WRITE_JSON_t PWM_WRITE_JSON;//PWMд������
	PWM_READ_JSON_t PWM_READ_JSON;//PWM��ȡ����
	PWM_REBACK_JSON_t PWM_REBACK_JSON;//PWM��ȡ��ķ�������
}PWM_JSON_t;

/******UART_JSON******/
//д������
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��WRITE-UART
	int channel;//ͨ��ID��int�������ݣ����磺1
	char* data;//�Զ������ݣ�string�������ݣ������Լ������Լ������
}UART_WRITE_JSON_t;

//��ȡ����
typedef struct
{
	char* type;//string�������ݣ�����ֵ��READ-UART
	int channel;//ͨ��ID��int�������ݣ����磺1
	char* data_last_t;
}UART_READ_JSON_t;

//��ȡ���غ������
typedef struct
{
	char* type;//��ǰ��ȡ�������ͣ�string��������
	int channel;//��ǰͨ��ID��int��������
	char* data;//�Զ������ݣ�string��������
}UART_REBACK_JSON_t;

//UART�������ݽ���
typedef struct
{
	UART_WRITE_JSON_t UART_WRITE_JSON;
	UART_READ_JSON_t UART_READ_JSON;
	UART_REBACK_JSON_t UART_REBACK_JSON;
}UART_JSON_t;

/******IMU_JSON******/
//��ȡ����
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��READ-IMU
}IMU_READ_JSON_t;

//��ȡ��ķ�������
typedef struct
{
	char* type;//��ǰ��ȡ�������ͣ�string��������
	float* X;//��ǰ�Ƕ�x���ݣ�float��������
	float* Y;//��ǰ�Ƕ�y���ݣ�float��������
	float* Z;//��ǰ�Ƕ�z���ݣ�float��������
	float* temperature;//��ǰ�¶ȣ�float��������
	float* pressure;//��ǰ��ѹ��float��������
}IMU_REBACK_JSON_t;

//IMU���ݽ���
typedef struct
{
	IMU_READ_JSON_t IMU_READ_JSON;
	IMU_REBACK_JSON_t IMU_REBACK_JSON;
}IMU_JSON_t;

/******POWER_5V/24V_JSON******/
//5V��Դд������
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��WRITE-POWER5
	int channel;//ͨ��ID��int�������ݣ����磺1
	char* status;//����״̬��string�������ݣ����ò�����OFF��ON
}POWER_5V_JSON_t;

//24V��Դд������
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��WRITE-POWER24
	int channel;//ͨ��ID��int�������ݣ����磺1
	char* status;//����״̬��string�������ݣ����ò�����OFF��ON
}POWER_24V_JSON_t;

/******POWER_LIMIT_JSON******/
//��ȡ����
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��READ-POWER
}POWER_READ_JSON_t;

//��ȡ��ķ�������
typedef struct
{
	char* type;//��ǰ��ȡ�������ͣ�string��������
	float* voltage;//��ǰ��ѹ���ݣ�float��������
}POWER_REBACK_JSON_t;

//��Դ�������ݽ���
typedef struct
{
	POWER_READ_JSON_t POWER_READ_JSON;
	POWER_REBACK_JSON_t POWER_REBACK_JSON;
}POWER_LIMIT_JSON_t;

/******BUZZER_JSON******/
//������д������
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��WRITE-BUZZER
	int tone;//������string��������
}BUZZER_WIRTE_JSON_t;

//ѡ������
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��WRITE-SONG
	char* music;//ѡ�����ף�string�������ݣ�����ֵ����С���ǡ�,��ǧ��ǧѰ��
	int speed;//�����ٶȣ�int�������ݣ�����ֵ��1-9������5
}BUZZER_SONG_JSON_t;

//ֹͣ����
typedef struct
{
	char* type;//�������ͣ�string�������ݣ�����ֵ��STOP-BUZZER
}BUZZER_STOP_JSON_t;

//���������ݽ���
typedef struct
{
	BUZZER_WIRTE_JSON_t BUZZER_WIRTE_JSON;
	BUZZER_SONG_JSON_t BUZZER_SONG_JSON;
	BUZZER_STOP_JSON_t BUZZER_STOP_JSON;
}BUZZER_JSON_t;

/******TF_CARD_JSON******/
//д������
typedef struct
{
	char* type;
	char* file;
	char* data;
}TF_CARD_WRITE_JSON_t;

//׷������
typedef struct
{
	char* type;
	char* file;
	char* data;
}TF_CARD_ADD_JSON_t;

//��ȡ����
typedef struct
{
	char* type;
	char* file;
}TF_CARD_READ_JSON_t;

//ɾ������
typedef struct
{
	char* type;
	char* file;
}TF_CARD_DELETE_JSON_t;

//��ȡ��ķ�������
typedef struct
{
	char* type;
	char* file;
	char* data;
}TF_CARD_REBACK_JSON_t;

//TF�����ݽ���
typedef struct
{
	TF_CARD_WRITE_JSON_t TF_CARD_WRITE_JSON;
	TF_CARD_ADD_JSON_t TF_CARD_ADD_JSON;
	TF_CARD_READ_JSON_t TF_CARD_READ_JSON;
	TF_CARD_DELETE_JSON_t TF_CARD_DELETE_JSON;
	TF_CARD_REBACK_JSON_t TF_CARD_REBACK_JSON;
}TF_CARD_JSON_t;

/******ALL_JSON******/
//����json���ݽ����ṹ��
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
