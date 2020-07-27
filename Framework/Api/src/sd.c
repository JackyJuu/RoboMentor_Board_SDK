#include "sd.h"

#include "sd_card.h"
#include "ff_debug.h"
#include "ff.h"

#include "Cjson_Task.h"
#include "Mission_task.h"

extern int TF_flag;
extern int SD_FLAG;


#if USART1_TF_DEBUG == 1
void TF_file_delete(char* filename_t)
{
	FRESULT		fresult;
	FATFS   	fs;
	TCHAR		filename[16];
	printf("{  \r\n");	
	printf("f_mount:");
	fresult = f_mount(0, &fs);
	FR_print_error(fresult);
	
	sprintf(filename,"0:%s",filename_t);
	fresult = f_unlink(filename);
	FR_print_error(fresult);
	
	f_mount(0, NULL);
	printf("}  \r\n");
	
}

void TF_file_add(char* filename_t, char* data)
{
	int i;
 	FATFS   	fs;
	FIL     	file;
	FRESULT		fresult;
	TCHAR		filename[128];
		
	int byte;
		
	printf("{  \r\n");	
	//注册一个工作区域
	printf("f_mount:");
	fresult = f_mount(0, &fs);
	FR_print_error(fresult);

	sprintf(filename,"0:%s",filename_t);
	printf("f_open: %s\n",filename);
	fresult = f_open(&file, filename, FA_OPEN_EXISTING | FA_WRITE);
	FR_print_error(fresult);
	
	byte = f_size(&file);
	printf("test_byte1 : %d  \r\n",byte);
	f_lseek(&file, byte);
	
	
	printf("f_printf:");
	i = f_printf(&file,data);
	printf(" %s",data);
	printf("\r\n");
	
	printf("f_close:\r\n");
	fresult = f_close(&file);
	FR_print_error(fresult);
//注销一个工作区域
	f_mount(0, NULL);
	printf("}  \r\n");
}

void TF_file_read(char* filename_t,char* data)
{
 	FATFS   	fs;
	FIL     	file;
	FRESULT		fresult;
	TCHAR		buffstr[1024];
	TCHAR		filename[128];
			int byte;

	printf("{  \r\n");
		
	//注册/注销一个工作区域
	printf("f_mount:");
	fresult = f_mount(0, &fs);
	FR_print_error(fresult);


	//=========================================================================
	//打开一个文件
	sprintf(filename,"0:%s",filename_t);
	printf("f_open: %s\r\n",filename);
	fresult = f_open(&file, filename, FA_OPEN_EXISTING | FA_READ);
	FR_print_error(fresult);
	
	
	byte = f_size(&file);
	printf("test_byte : %d  \r\n",byte);
	printf("f_read:\r\n");
	f_lseek(&file, 0);
	fresult = f_read(&file,buffstr,byte,0);
	
	FR_print_error(fresult);
	
	printf("f_close:\r\n");
	fresult = f_close(&file);
	FR_print_error(fresult);

		for(int i = byte;i <= 256;i++)
		{
			buffstr[i] = NULL;
		}
		for(int i = 0;i < byte;i++)
		{
			data[i] = buffstr[i];
		}
		
		printf("data:%s \r\n",buffstr);

	f_mount(0, NULL);
	printf("}  \r\n");
}


void TF_file_write(char* filename_t, char* data)
{
	uint32_t 	i = 0;
 	FATFS   	fs;
	FIL     	file;
	FRESULT		fresult;
	TCHAR		filename[128];
		
	printf("{  \r\n");
		
	//注册/注销一个工作区域
	printf("f_mount:");
	fresult = f_mount(0, &fs);
	FR_print_error(fresult);

	//=========================================================================
	//创建/打开一个文件
	printf("f_open:");
	sprintf(filename,"0:%s",filename_t);
	printf("%s\r\n",filename);
	fresult = f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE);
	FR_print_error(fresult);
	
	//写一个格式化的字符串
	printf("f_printf:");
	i = f_printf(&file,data);
	printf(" %s",data);
	printf("\r\n");
			
	//关闭一个文件
	printf("f_close:\r\n");
	fresult = f_close(&file);
	FR_print_error(fresult);
	f_mount(0, NULL);
	printf("}  \r\n");
}
#else
void TF_file_delete(char* filename_t)
{
	volatile FRESULT		fresult;
	FATFS   	fs;
	TCHAR		filename[16];
	fresult = f_mount(0, &fs);
	
	sprintf(filename,"0:%s",filename_t);
	fresult = f_unlink(filename);

	f_mount(0, NULL);
	
}

void TF_file_add(char* filename_t, char* data)
{
	volatile int i;
 	FATFS   	fs;
	FIL     	file;
	volatile FRESULT		fresult;
	TCHAR		filename[128];
		
	int byte;
		
	fresult = f_mount(0, &fs);

	sprintf(filename,"0:%s",filename_t);
	
	fresult = f_open(&file, filename, FA_OPEN_EXISTING | FA_WRITE);
	
	byte = f_size(&file);

	f_lseek(&file, byte);
	i = f_printf(&file,data);
	
	fresult = f_close(&file);

//注销一个工作区域
	f_mount(0, NULL);
}

void TF_file_read(char* filename_t,char* data)
{
 	FATFS   	fs;
	FIL     	file;
	volatile FRESULT		fresult;
	TCHAR		buffstr[1024];
	TCHAR		filename[128];
	int byte;
		
	fresult = f_mount(0, &fs);
	
	//=========================================================================
	//打开一个文件
	sprintf(filename,"0:%s",filename_t);
	fresult = f_open(&file, filename, FA_OPEN_EXISTING | FA_READ);
	
	byte = f_size(&file);
	f_lseek(&file, 0);
	fresult = f_read(&file,buffstr,byte,0);
	
	fresult = f_close(&file);

		for(int i = byte;i <= 256;i++)
		{
			buffstr[i] = NULL;
		}
		for(int i = 0;i < byte;i++)
		{
			data[i] = buffstr[i];
		}
		
	f_mount(0, NULL);
}


void TF_file_write(char* filename_t, char* data)
{
	volatile uint32_t 	i = 0;
 	FATFS   	fs;
	FIL     	file;
	volatile FRESULT		fresult;
	TCHAR		filename[128];
		
		
	fresult = f_mount(0, &fs);

	sprintf(filename,"0:%s",filename_t);
	fresult = f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE);
	
	i = f_printf(&file,data);
			
	fresult = f_close(&file);
	f_mount(0, NULL);
}

#endif
