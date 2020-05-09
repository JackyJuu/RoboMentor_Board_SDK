#ifndef _IO_H_
#define _IO_H_

typedef enum
{
	PE3 = 1,
	PH14 = 2,
	PE9,
	PH15,
	PE10,
	PI1,
	PE12,
	PI3,
	PF2,
	PI4,
	PF11,
	PI8,
	PF12,
	PI9,
	PF13,
	PI10,
	PF15,
	PI11,
}USER_IO_t;

typedef enum
{
	USER_IO_Mode_In,
	USER_IO_Mode_Out
}USER_IO_MODE_t;

typedef enum
{
	High_Level,
	Low_Level,
	Toggle_Level	
}USER_IO_Out_t;

void User_Io_Init(USER_IO_t USER_IO,USER_IO_MODE_t USER_IO_MODE);
void User_Out_Set(USER_IO_t USER_IO,USER_IO_Out_t USER_IO_Out);
int User_Io_Scan(USER_IO_t USER_IO);


#endif
