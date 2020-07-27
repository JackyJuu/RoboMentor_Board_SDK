#include "io.h"
#include "All_define.h"

void User_Io_Init(USER_IO_t USER_IO,USER_IO_MODE_t USER_IO_MODE)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	if(USER_IO == PE3)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOE,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
		}	
	}
	else if(USER_IO == PH14)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOH,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
		}	
	}
	else if(USER_IO == PE9)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOE,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		}	
	}
	else if(USER_IO == PH15)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOH,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOH, &GPIO_InitStructure);
		}		
	}
	else if(USER_IO == PE10)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOE,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		}	
	}
	else if(USER_IO == PI1)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PE12)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOE,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PI3)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PF2)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOF,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOF, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PI4)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PF11)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOF,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOF, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PI8)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PF12)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOF,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOF, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PI9)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PF13)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOF,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOF, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PI10)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PF15)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOF,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOF, &GPIO_InitStructure);
		}
	}
	else if(USER_IO == PI11)
	{
		if(USER_IO_MODE == USER_IO_Mode_Out)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_Init(GPIOI,&GPIO_InitStructure);
		}
		else if(USER_IO_MODE == USER_IO_Mode_In)
		{
		 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOI, &GPIO_InitStructure);
		}
	}	
}

int User_Io_Scan(USER_IO_t USER_IO)
{
	switch(USER_IO)
	{
		case 1:
		{
			return USER_IO_PE3_READ;
		}
		case 2:
		{
			return USER_IO_PH14_READ;
		}
		case 3:
		{
			return USER_IO_PE9_READ;	
		}
		case 4:
		{
			return USER_IO_PH15_READ;
		}
		case 5:
		{
			return USER_IO_PE10_READ;
		}
		case 6:
		{
			return USER_IO_PI1_READ;
		}
		case 7:
		{
			return USER_IO_PE12_READ;
		}
		case 8:
		{
			return USER_IO_PI3_READ;
		}
		case 9:
		{
			return USER_IO_PF2_READ;
		}
		case 10:
		{
			return USER_IO_PI4_READ;
		}
		case 11:
		{
			return USER_IO_PF11_READ;
		}
		case 12:
		{
			return USER_IO_PI8_READ;
		}
		case 13:
		{
			return USER_IO_PF12_READ;
		}
		case 14:
		{
			return USER_IO_PI9_READ;
		}
		case 15:
		{
			return USER_IO_PF13_READ;
		}
		case 16:
		{
			return USER_IO_PI10_READ;
		}
		case 17:
		{
			return USER_IO_PF15_READ;
		}
		case 18:
		{
			return USER_IO_PI11_READ;
		}
	}
	return 0;
}

void User_Out_Set(USER_IO_t USER_IO,USER_IO_Out_t USER_IO_Out)
{
	switch(USER_IO)
	{
		case 1:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PE3_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PE3_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PE3_TOGGLE();
			}
			break;
		}
		case 2:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PH14_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PH14_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PH14_TOGGLE();
			}
			break;
		}
		case 3:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PE9_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PE9_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PE9_TOGGLE();
			}
			break;
		}
		case 4:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PH15_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PH15_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PH15_TOGGLE();
			}
			break;
		}
		case 5:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PE10_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PE10_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PE10_TOGGLE();
			}
			break;
		}
		case 6:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PI1_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PI1_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PI1_TOGGLE();
			}
			break;
		}
		case 7:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PE12_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PE12_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PE12_TOGGLE();
			}
			break;
		}
		case 8:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PI3_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PI3_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PI3_TOGGLE();
			}
			break;
		}
		case 9:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PF2_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PF2_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PF2_TOGGLE();
			}
			break;
		}
		case 10:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PI4_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PI4_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PI4_TOGGLE();
			}
			break;
		}
		case 11:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PF11_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PF11_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PF11_TOGGLE();
			}
			break;
		}
		case 12:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PI8_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PI8_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PI8_TOGGLE();
			}
			break;
		}
		case 13:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PF12_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PF12_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PF12_TOGGLE();
			}
			break;
		}
		case 14:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PI9_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PI9_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PI9_TOGGLE();
			}
			break;
		}
		case 15:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PF13_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PF13_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PF13_TOGGLE();
			}
			break;
		}
		case 16:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PI10_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PI10_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PI10_TOGGLE();
			}
			break;
		}
		case 17:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PF15_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PF15_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PF15_TOGGLE();
			}
			break;
		}
		case 18:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PI11_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PI11_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PI11_TOGGLE();
			}
			break;
		}
		case 19:
		{
			if(USER_IO_Out == High_Level)
			{
				USER_IO_PE3_HIGH();
				USER_IO_PH14_HIGH();
				USER_IO_PE9_HIGH();
				USER_IO_PH15_HIGH();
				USER_IO_PE10_HIGH();
				USER_IO_PI1_HIGH();
				USER_IO_PE12_HIGH();
				USER_IO_PI3_HIGH();
				USER_IO_PF2_HIGH();
				USER_IO_PI4_HIGH();
				USER_IO_PF11_HIGH();
				USER_IO_PI8_HIGH();
				USER_IO_PF12_HIGH();
				USER_IO_PI9_HIGH();
				USER_IO_PF13_HIGH();
				USER_IO_PI10_HIGH();
				USER_IO_PF15_HIGH();
				USER_IO_PI11_HIGH();
			}
			else if(USER_IO_Out == Low_Level)
			{
				USER_IO_PE3_LOW();
				USER_IO_PH14_LOW();
				USER_IO_PE9_LOW();
				USER_IO_PH15_LOW();
				USER_IO_PE10_LOW();
				USER_IO_PI1_LOW();
				USER_IO_PE12_LOW();
				USER_IO_PI3_LOW();
				USER_IO_PF2_LOW();
				USER_IO_PI4_LOW();
				USER_IO_PF11_LOW();
				USER_IO_PI8_LOW();
				USER_IO_PF12_LOW();
				USER_IO_PI9_LOW();
				USER_IO_PF13_LOW();
				USER_IO_PI10_LOW();
				USER_IO_PF15_LOW();
				USER_IO_PI11_LOW();
			}
			else if(USER_IO_Out == Toggle_Level)
			{
				USER_IO_PE3_TOGGLE();
				USER_IO_PH14_TOGGLE();
				USER_IO_PE9_TOGGLE();
				USER_IO_PH15_TOGGLE();
				USER_IO_PE10_TOGGLE();
				USER_IO_PI1_TOGGLE();
				USER_IO_PE12_TOGGLE();
				USER_IO_PI3_TOGGLE();
				USER_IO_PF2_TOGGLE();
				USER_IO_PI4_TOGGLE();
				USER_IO_PF11_TOGGLE();
				USER_IO_PI8_TOGGLE();
				USER_IO_PF12_TOGGLE();
				USER_IO_PI9_TOGGLE();
				USER_IO_PF13_TOGGLE();
				USER_IO_PI10_TOGGLE();
				USER_IO_PF15_TOGGLE();
				USER_IO_PI11_TOGGLE();
			}
			break;
		}
	}
}
