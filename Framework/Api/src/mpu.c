#include "stm32f4xx.h"
#include "mpu_9250.h"
#include "spi.h"
#include "imu.h"
#include "delay.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

#define MPU_ENABLE            GPIO_ResetBits(GPIOF, GPIO_Pin_6)
#define MPU_DISABLE           GPIO_SetBits(GPIOF, GPIO_Pin_6)

#define Kp 2.0f                                              /* 
                                                              * proportional gain governs rate of 
                                                              * convergence to accelerometer/magnetometer 
																															*/
#define Ki 0.01f                                             /* 
                                                              * integral gain governs rate of 
                                                              * convergence of gyroscope biases 
																															*/
																															
#define AUX_READ_TIMEOUT      (200)

/*bmp280 气压和温度过采样 工作模式*/
#define BMP280_PRESSURE_OSR			(BMP280_OVERSAMP_8X)
#define BMP280_TEMPERATURE_OSR		(BMP280_OVERSAMP_16X)
#define BMP280_MODE					(BMP280_PRESSURE_OSR << 2 | BMP280_TEMPERATURE_OSR << 5 | BMP280_NORMAL_MODE)



typedef struct 
{
    u16 dig_T1;	/* calibration T1 data */
    s16 dig_T2; /* calibration T2 data */
    s16 dig_T3; /* calibration T3 data */
    u16 dig_P1;	/* calibration P1 data */
    s16 dig_P2; /* calibration P2 data */
    s16 dig_P3; /* calibration P3 data */
    s16 dig_P4; /* calibration P4 data */
    s16 dig_P5; /* calibration P5 data */
    s16 dig_P6; /* calibration P6 data */
    s16 dig_P7; /* calibration P7 data */
    s16 dig_P8; /* calibration P8 data */
    s16 dig_P9; /* calibration P9 data */
    s32 t_fine; /* calibration t_fine data */
} bmp280Calib;

bmp280Calib  bmp280Cal;

static int32_t bmp280RawPressure = 0;
static int32_t bmp280RawTemperature = 0;

static uint8_t ak_asa_data[3];

static void bmp280GetPressure(void);

float pressure;
float temperature;
float altitude;

volatile float        q0 = 1.0f;
volatile float        q1 = 0.0f;
volatile float        q2 = 0.0f;
volatile float        q3 = 0.0f;
volatile float        exInt, eyInt, ezInt;                   /* error integral */
static volatile float gx, gy, gz, ax, ay, az, mx, my, mz;  
unsigned long     last_update, now_update;               /* Sampling cycle count, ubit ms */

uint8_t               mpu_buff[28];                          /* buffer to save imu raw data */
uint8_t               ak_buff[6];                           /* buffer to save AK8963 raw data */
mpu_data_t            mpu_data;
imu_t                 imu={0};

/**
  * @brief  fast inverse square-root, to calculate 1/Sqrt(x)
  * @param  x: the number need to be calculated
  * @retval 1/Sqrt(x)
  * @usage  call in imu_ahrs_update() function
  */
float inv_sqrt(float x) 
{
	float halfx = 0.5f * x;
	float y     = x;
	long  i     = *(long*)&y;
	
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	
	return y;
}



/**
  * @brief  write a byte of data to specified register
  * @param  reg:  the address of register to be written
  *         data: data to be written
  * @retval 
  * @usage  call in ist_reg_write_by_mpu(),         
  *                 ist_reg_read_by_mpu(), 
  *                 mpu_master_i2c_auto_read_config(), 
  *                 ist8310_init(), 
  *                 mpu_set_gyro_fsr(),             
  *                 mpu_set_accel_fsr(), 
  *                 mpu_device_init() function
  */
uint8_t mpu_write_byte(uint8_t const reg, uint8_t const data)
{
	MPU_ENABLE;
	
	/* Transmit the first address for write operation */
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
		
	}
	SPI_I2S_SendData(SPI5, reg & 0x7F);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
		
	}
	SPI_I2S_ReceiveData(SPI5);
	
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
		
	}
	SPI_I2S_SendData(SPI5, data);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
		
	}
	SPI_I2S_ReceiveData(SPI5);

	MPU_DISABLE;
	return 0;
}

/**
  * @brief  read a byte of data from specified register
  * @param  reg: the address of register to be read
  * @retval 
  * @usage  call in ist_reg_read_by_mpu(),         
  *                 mpu_device_init() function
  */
uint8_t mpu_read_byte(uint8_t const reg)
{
	uint8_t data = 0;
	MPU_ENABLE;
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
		
	}
	SPI_I2S_SendData(SPI5, reg | 0x80);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
		
	}
	SPI_I2S_ReceiveData(SPI5);
	
	
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
		
	}
	SPI_I2S_SendData(SPI5, 0x00);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
		
	}
	data = SPI_I2S_ReceiveData(SPI5);
	MPU_DISABLE;
	return data;
}

/**
  * @brief  read bytes of data from specified register
  * @param  reg: address from where data is to be written
  * @retval 
  */
uint8_t mpu_read_bytes(uint8_t const regAddr, uint8_t* pData, uint8_t len)
{
	int i = 0;
	MPU_ENABLE;
	
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
	{
		
	}
	SPI_I2S_SendData(SPI5, regAddr | 0x80);
	while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
	{
		
	}
	SPI_I2S_ReceiveData(SPI5);
	
	for(i=0; i<len; i++)
	{
		while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
		{
			
		}
		SPI_I2S_SendData(SPI5, 0x00);
		while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
		{

		}
		pData[i] = SPI_I2S_ReceiveData(SPI5);
	}
	
	MPU_DISABLE;
	return 0;
}

void MPU92_AUX_WriteReg( uint8_t slaveAddr, uint8_t writeAddr, uint8_t writeData )
{
  uint8_t  status;
  uint32_t timeout = AUX_READ_TIMEOUT;

  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV4_ADDR, slaveAddr);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV4_REG, writeAddr);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV4_DO, writeData);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV4_CTRL, MPUREG_I2C_SLVx_EN);

  do
	{
    Delay_ms(1);
    status = mpu_read_byte(MPUREG_I2C_MST_STATUS);
  } while (((status & MPUREG_I2C_SLV4_DONE) == 0) && (timeout--));
  Delay_ms(1);
}


uint8_t MPU92_AUX_ReadReg( uint8_t slaveAddr, uint8_t readAddr )
{
  uint8_t status;
  uint8_t readData;
  uint32_t timeout = AUX_READ_TIMEOUT;

  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV4_ADDR, slaveAddr | 0x80);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV4_REG, readAddr);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV4_CTRL, MPUREG_I2C_SLVx_EN);

  do
	{
    Delay_ms(1);
    status = mpu_read_byte(MPUREG_I2C_MST_STATUS);
  } while (((status & MPUREG_I2C_SLV4_DONE) == 0) && (timeout--));
  Delay_ms(1);
  readData = mpu_read_byte(MPUREG_I2C_SLV4_DI);

  return readData;
}


static void MPU92_AUX_SlaveConfig( uint8_t slaveNum, uint8_t slaveAddr, uint8_t readAddr, uint8_t readLens )
{
  uint8_t reg;
  uint8_t offset = slaveNum * 3;

  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV0_ADDR + offset, slaveAddr | 0x80);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV0_REG + offset, readAddr);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV0_CTRL + offset, MPUREG_I2C_SLVx_EN | readLens);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_SLV4_CTRL, 0x01);
  Delay_ms(1);
  reg = mpu_read_byte(MPUREG_I2C_MST_DELAY_CTRL);
  Delay_ms(1);
  mpu_write_byte(MPUREG_I2C_MST_DELAY_CTRL, reg | (0x01 << slaveNum));
}







/**
	* @brief  Initializes the AK8963 device
	* @param  
	* @retval 
  * @usage  call in mpu_device_init() function
	*/
uint8_t ak8963_init()
{
	volatile uint8_t res, asa[3] = {0};
	/* enable iic master mode */
	mpu_write_byte(MPUREG_USER_CTRL, 0x30);
	Delay_ms(10);
	/* enable iic 400khz */
	mpu_write_byte(MPUREG_I2C_MST_CTRL, 0x5d); 
	Delay_ms(10);
	mpu_write_byte(MPUREG_I2C_MST_DELAY_CTRL, 0x80);
	Delay_ms(10);
	
	MPU92_AUX_WriteReg(AK8963_I2C_ADDR, AK8963REG_CNTL2, 0x01);    // Reset Device
	Delay_ms(50);
	MPU92_AUX_WriteReg(AK8963_I2C_ADDR, AK8963REG_CNTL1, 0x00);    // Power-down mode
  Delay_ms(1);
  MPU92_AUX_WriteReg(AK8963_I2C_ADDR, AK8963REG_CNTL1, 0x1F);    // Fuse ROM access mode, Read sensitivity adjustment
  Delay_ms(10);
  ak_asa_data[0] = MPU92_AUX_ReadReg(AK8963_I2C_ADDR, AK8963REG_ASAX);
  Delay_ms(1);
  ak_asa_data[1] = MPU92_AUX_ReadReg(AK8963_I2C_ADDR, AK8963REG_ASAY);
  Delay_ms(1);
  ak_asa_data
	[2] = MPU92_AUX_ReadReg(AK8963_I2C_ADDR, AK8963REG_ASAZ);
  Delay_ms(1);
	
	
	MPU92_AUX_WriteReg(AK8963_I2C_ADDR, AK8963REG_CNTL1, 0x00);    // Power-down mode
	Delay_ms(10);
	MPU92_AUX_WriteReg(AK8963_I2C_ADDR, AK8963REG_CNTL1, 0x16);    // Continuous measurement mode 2 & 16-bit
	Delay_ms(10);
	
	
	
	MPU92_AUX_SlaveConfig(0, AK8963_I2C_ADDR, AK8963REG_ST1, 8);

	return 0;
}


void bmp280Init()
{
	int i = 0;
	for(i = 0; i < 24; i++)
	{
		((uint8_t *)&bmp280Cal)[i] = MPU92_AUX_ReadReg(BMP280_I2C_ADDR, BMP280_TEMPERATURE_CALIB_DIG_T1_LSB_REG + i);
	}
	
	MPU92_AUX_WriteReg(BMP280_I2C_ADDR, BMP280_CTRL_MEAS_REG, BMP280_MODE);
	MPU92_AUX_WriteReg(BMP280_I2C_ADDR, BMP280_CONFIG_REG, 5<<2);		/*配置IIR滤波*/
	
	MPU92_AUX_SlaveConfig(1, BMP280_I2C_ADDR, BMP280_PRESSURE_MSB_REG, 6);
}


static void bmp280GetPressure(void)
{
    u8 data[BMP280_DATA_FRAME_SIZE];

    // read data from sensor
//    i2cdevRead(I2Cx, devAddr, BMP280_PRESSURE_MSB_REG, BMP280_DATA_FRAME_SIZE, data);
    bmp280RawPressure = (s32)((((uint32_t)(data[0])) << 12) | (((uint32_t)(data[1])) << 4) | ((uint32_t)data[2] >> 4));
    bmp280RawTemperature = (s32)((((uint32_t)(data[3])) << 12) | (((uint32_t)(data[4])) << 4) | ((uint32_t)data[5] >> 4));
}

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of "5123" equals 51.23 DegC
// t_fine carries fine temperature as global value
u32 bmp280CompensateT(s32 adcT)
{
    s32 var1, var2, T;

    var1 = ((((adcT >> 3) - ((s32)bmp280Cal.dig_T1 << 1))) * ((s32)bmp280Cal.dig_T2)) >> 11;
    var2  = (((((adcT >> 4) - ((s32)bmp280Cal.dig_T1)) * ((adcT >> 4) - ((s32)bmp280Cal.dig_T1))) >> 12) * ((s32)bmp280Cal.dig_T3)) >> 14;
    bmp280Cal.t_fine = var1 + var2;
	
    T = (bmp280Cal.t_fine * 5 + 128) >> 8;

    return T;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of "24674867" represents 24674867/256 = 96386.2 Pa = 963.862 hPa
u32 bmp280CompensateP(s32 adcP)
{
    int64_t var1, var2, p;
    var1 = ((int64_t)bmp280Cal.t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)bmp280Cal.dig_P6;
    var2 = var2 + ((var1*(int64_t)bmp280Cal.dig_P5) << 17);
    var2 = var2 + (((int64_t)bmp280Cal.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)bmp280Cal.dig_P3) >> 8) + ((var1 * (int64_t)bmp280Cal.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)bmp280Cal.dig_P1) >> 33;
    if (var1 == 0)
        return 0;
    p = 1048576 - adcP;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)bmp280Cal.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)bmp280Cal.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)bmp280Cal.dig_P7) << 4);
    return (uint32_t)p;
}

#define FILTER_NUM	5
#define FILTER_A	0.1f

/*限幅平均滤波法*/
void pressureFilter(float* in, float* out)
{	
	static u8 i=0;
	static float filter_buf[FILTER_NUM]={0.0};
	double filter_sum=0.0;
	u8 cnt=0;	
	float deta;		
	
	if(filter_buf[i] == 0.0f)
	{
		filter_buf[i]=*in;
		*out=*in;
		if(++i>=FILTER_NUM)	i=0;
	} else 
	{
		if(i) deta=*in-filter_buf[i-1];
		else deta=*in-filter_buf[FILTER_NUM-1];
		
		if(fabs(deta)<FILTER_A)
		{
			filter_buf[i]=*in;
			if(++i>=FILTER_NUM)	i=0;
		}
		for(cnt=0;cnt<FILTER_NUM;cnt++)
		{
			filter_sum+=filter_buf[cnt];
		}
		*out=filter_sum /FILTER_NUM;
	}
}

void bmp280GetData(float* pressure, float* temperature, float* asl)
{
    static float t;
    static float p;
	
	bmp280GetPressure();

	t = bmp280CompensateT(bmp280RawTemperature)/100.0;		
	p = bmp280CompensateP(bmp280RawPressure)/25600.0;		

	pressureFilter(&p,pressure);
	*temperature = (float)t;/*单位度*/
//	*pressure = (float)p ;	/*单位hPa*/	
	
	*asl=bmp280PressureToAltitude(pressure);	/*转换成海拔*/	
}

#define CONST_PF 0.1902630958	//(1/5.25588f) Pressure factor
#define FIX_TEMP 25				// Fixed Temperature. ASL is a function of pressure and temperature, but as the temperature changes so much (blow a little towards the flie and watch it drop 5 degrees) it corrupts the ASL estimates.
								// TLDR: Adjusting for temp changes does more harm than good.
/**
 * Converts pressure to altitude above sea level (ASL) in meters
 */
float bmp280PressureToAltitude(float* pressure/*, float* groundPressure, float* groundTemp*/)
{
    if (*pressure > 0)
    {
        return ((pow((1015.7f / *pressure), CONST_PF) - 1.0f) * (FIX_TEMP + 273.15f)) / 0.0065f;
    }
    else
    {
        return 0;
    }
}







/**
	* @brief  get the data of AK8963
  * @param  buff: the buffer to save the data of AK8963
	* @retval 
  * @usage  call in mpu_get_data() function
	*/
void ak8963_get_data(uint8_t* buff)
{
    mpu_read_bytes(MPUREG_EXT_SENS_DATA_00, buff, 6); 
}


/**
	* @brief  get the data of imu
  * @param  
	* @retval 
  * @usage  call in main() function
	*/
void mpu_get_data(void)
{
	static float t;
	static float p;
	
	mpu_read_bytes(MPUREG_ACCEL_XOUT_H, mpu_buff, 28);

	mpu_data.ax   = mpu_buff[0] << 8 | mpu_buff[1];
	mpu_data.ay   = mpu_buff[2] << 8 | mpu_buff[3];
	mpu_data.az   = mpu_buff[4] << 8 | mpu_buff[5];
	mpu_data.temp = mpu_buff[6] << 8 | mpu_buff[7];

	mpu_data.gx = ((mpu_buff[8]  << 8 | mpu_buff[9])  - mpu_data.gx_offset);
	mpu_data.gy = ((mpu_buff[10] << 8 | mpu_buff[11]) - mpu_data.gy_offset);
	mpu_data.gz = ((mpu_buff[12] << 8 | mpu_buff[13]) - mpu_data.gz_offset);
	
	if(mpu_buff[14] == 1)
	{
	mpu_data.mx = (mpu_buff[16] << 8) | mpu_buff[15];  /* Mag.X */
	mpu_data.my = (mpu_buff[18] << 8) | mpu_buff[17];  /* Mag.Y */
	mpu_data.mz = (mpu_buff[20] << 8) | mpu_buff[19];  /* Mag.Z */
	}
	imu.mx = mpu_data.mx * (((ak_asa_data[0]-128) * 0.5)/128 + 1);
	imu.my = mpu_data.my * (((ak_asa_data[1]-128) * 0.5)/128 + 1);
	imu.mz = mpu_data.mz * (((ak_asa_data[2]-128) * 0.5)/128 + 1);

	memcpy(&imu.ax, &mpu_data.ax, 3 * sizeof(int16_t));

	imu.temp = 21 + mpu_data.temp / 333.87f;
	/* 2000dps -> rad/s */
	imu.wx   = mpu_data.gx / 16.384f / 57.3f; 
	imu.wy   = mpu_data.gy / 16.384f / 57.3f; 
	imu.wz   = mpu_data.gz / 16.384f / 57.3f;
	
	
	bmp280RawPressure = (s32)((((uint32_t)(mpu_buff[22])) << 12) | (((uint32_t)(mpu_buff[23])) << 4) | ((uint32_t)mpu_buff[24] >> 4));
	bmp280RawTemperature = (s32)((((uint32_t)(mpu_buff[25])) << 12) | (((uint32_t)(mpu_buff[26])) << 4) | ((uint32_t)mpu_buff[27] >> 4));
	
	
	
	t = bmp280CompensateT(bmp280RawTemperature)/100.0;		
	p = bmp280CompensateP(bmp280RawPressure)/25600.0;		
	
	pressureFilter(&p, &pressure);
	temperature = (float)t;/*单位度*/
//	*pressure = (float)p ;	/*单位hPa*/	
	
	altitude = bmp280PressureToAltitude(&pressure);	/*转换成海拔*/	
	
	
	
	
	
}


/**
	* @brief  set imu 6500 gyroscope measure range
  * @param  fsr: range(0,?50dps;1,?00dps;2,?000dps;3,?000dps)
	* @retval 
  * @usage  call in mpu_device_init() function
	*/
uint8_t mpu_set_gyro_fsr(uint8_t fsr)
{
  return mpu_write_byte(MPUREG_GYRO_CONFIG, fsr << 3);
}


/**
	* @brief  set imu 6050/6500 accelerate measure range
  * @param  fsr: range(0,?g;1,?g;2,?g;3,?6g)
	* @retval 
  * @usage  call in mpu_device_init() function
	*/
uint8_t mpu_set_accel_fsr(uint8_t fsr)
{
  return mpu_write_byte(MPUREG_ACCEL_CONFIG, fsr << 3); 
}

uint8_t id;

/**
	* @brief  initialize imu mpu6500 and magnet meter ak8963
  * @param  
	* @retval 
  * @usage  call in main() function
	*/
uint8_t mpu_device_init(void)
{
	mpu_write_byte(MPUREG_USER_CTRL,0x00);
	Delay_ms(100);

	id                               = mpu_read_byte(MPUREG_WHOAMI);
	uint8_t i                        = 0;
	uint8_t MPUREG_Init_Data[10][2] = {{ MPUREG_PWR_MGMT_1, 0x80 },     /* Reset Device */ 
																		 { MPUREG_PWR_MGMT_1, 0x04 },     /* Clock Source - Gyro-Z */ 
																		 { MPUREG_PWR_MGMT_2, 0x00 },     /* Enable Acc & Gyro */ 
																		 { MPUREG_CONFIG, 0x04 },         /* LPF 41Hz */ 
																		 { MPUREG_GYRO_CONFIG, 0x18 },    /* +-2000dps */ 
																		 { MPUREG_ACCEL_CONFIG, 0x10 },   /* +-8G */ 
																		 { MPUREG_ACCEL_CONFIG2, 0x02 }, /* enable LowPassFilter  Set Acc LPF */ 
																		 { MPUREG_USER_CTRL, 0x30 },};    /* Enable AUX */ 
	
	if(MPU_WHOAMI_9250 != id)
	{
		while(1);
	}
																		 
	for (i = 0; i < 10; i++)
	{
		mpu_write_byte(MPUREG_Init_Data[i][0], MPUREG_Init_Data[i][1]);
		Delay_ms(1);
	}
	
	
	mpu_set_gyro_fsr(3); 		
	mpu_set_accel_fsr(2);

	ak8963_init();
	mpu_offset_call();
	return 0;
}

/**
	* @brief  get the offset data of MPU6500
  * @param  
	* @retval 
  * @usage  call in main() function
	*/
void mpu_offset_call(void)
{
	int i;
	for (i=0; i<300;i++)
	{
		mpu_read_bytes(MPUREG_ACCEL_XOUT_H, mpu_buff, 14);

		mpu_data.ax_offset += mpu_buff[0] << 8 | mpu_buff[1];
		mpu_data.ay_offset += mpu_buff[2] << 8 | mpu_buff[3];
		mpu_data.az_offset += mpu_buff[4] << 8 | mpu_buff[5];
	
		mpu_data.gx_offset += mpu_buff[8]  << 8 | mpu_buff[9];
		mpu_data.gy_offset += mpu_buff[10] << 8 | mpu_buff[11];
		mpu_data.gz_offset += mpu_buff[12] << 8 | mpu_buff[13];

		Delay_ms(5);
	}
	mpu_data.ax_offset=mpu_data.ax_offset / 300;
	mpu_data.ay_offset=mpu_data.ay_offset / 300;
	mpu_data.az_offset=mpu_data.az_offset / 300;
	mpu_data.gx_offset=mpu_data.gx_offset / 300;
	mpu_data.gy_offset=mpu_data.gx_offset / 300;
	mpu_data.gz_offset=mpu_data.gz_offset / 300;
}



/**
	* @brief  Initialize quaternion
  * @param  
	* @retval 
  * @usage  call in main() function
	*/
void init_quaternion(void)
{
	int16_t hx, hy;//hz;
	
	hx = imu.mx;
	hy = imu.my;
	//hz = imu.mz;
	
	if (hx < 0 && hy < 0) 
	{
		if (fabs(hx / hy) >= 1)
		{
			q0 = -0.005;
			q1 = -0.199;
			q2 = 0.979;
			q3 = -0.0089;
		}
		else
		{
			q0 = -0.008;
			q1 = -0.555;
			q2 = 0.83;
			q3 = -0.002;
		}
		
	}
	else if (hx < 0 && hy > 0)
	{
		if (fabs(hx / hy)>=1)   
		{
			q0 = 0.005;
			q1 = -0.199;
			q2 = -0.978;
			q3 = 0.012;
		}
		else
		{
			q0 = 0.005;
			q1 = -0.553;
			q2 = -0.83;
			q3 = -0.0023;
		}
		
	}
	else if (hx > 0 && hy > 0)
	{
		if (fabs(hx / hy) >= 1)
		{
			q0 = 0.0012;
			q1 = -0.978;
			q2 = -0.199;
			q3 = -0.005;
		}
		else
		{
			q0 = 0.0023;
			q1 = -0.83;
			q2 = -0.553;
			q3 = 0.0023;
		}
		
	}
	else if (hx > 0 && hy < 0)
	{
		if (fabs(hx / hy) >= 1)
		{
			q0 = 0.0025;
			q1 = 0.978;
			q2 = -0.199;
			q3 = 0.008;			
		}
		else
		{
			q0 = 0.0025;
			q1 = 0.83;
			q2 = -0.56;
			q3 = 0.0045;
		}		
	}
	
	
}

/**
	* @brief  update imu AHRS
  * @param  
	* @retval 
  * @usage  call in main() function
	*/
void imu_ahrs_update(void) 
{
	float norm;
	float hx, hy, hz, bx, bz;
	float vx, vy, vz, wx, wy, wz;
	float ex, ey, ez, halfT;
	float tempq0,tempq1,tempq2,tempq3;

	float q0q0 = q0*q0;
	float q0q1 = q0*q1;
	float q0q2 = q0*q2;
	float q0q3 = q0*q3;
	float q1q1 = q1*q1;
	float q1q2 = q1*q2;
	float q1q3 = q1*q3;
	float q2q2 = q2*q2;   
	float q2q3 = q2*q3;
	float q3q3 = q3*q3;   

	gx = imu.wx;
	gy = imu.wy;
	gz = imu.wz;
	
	ax = imu.ax;
	ay = imu.ay;
	az = imu.az;
	
	mx = imu.mx;
	my = imu.my;
	mz = imu.mz;

	get_tick_count(&now_update); //ms
	halfT       = ((float)(now_update - last_update) / 2000.0f);
	last_update = now_update;
	
	/* Fast inverse square-root */
	norm = inv_sqrt(ax*ax + ay*ay + az*az);       
	ax = ax * norm;
	ay = ay * norm;
	az = az * norm;
	
	#ifdef AK8963
	norm = inv_sqrt(mx*mx + my*my + mz*mz);          
	mx = mx * norm;
	my = my * norm;
		mz = mz * norm; 
	#else
	mx = 0;
	my = 0;
	mz = 0;		
	#endif
	
		
	/* compute reference direction of flux */
	hx = 2.0f*mx*(0.5f - q2q2 - q3q3) + 2.0f*my*(q1q2 - q0q3) + 2.0f*mz*(q1q3 + q0q2);
	hy = 2.0f*mx*(q1q2 + q0q3) + 2.0f*my*(0.5f - q1q1 - q3q3) + 2.0f*mz*(q2q3 - q0q1);
	hz = 2.0f*mx*(q1q3 - q0q2) + 2.0f*my*(q2q3 + q0q1) + 2.0f*mz*(0.5f - q1q1 - q2q2);         
	bx = sqrt((hx*hx) + (hy*hy));
	bz = hz; 
	
	/* estimated direction of gravity and flux (v and w) */
	vx = 2.0f*(q1q3 - q0q2);
	vy = 2.0f*(q0q1 + q2q3);
	vz = q0q0 - q1q1 - q2q2 + q3q3;
	wx = 2.0f*bx*(0.5f - q2q2 - q3q3) + 2.0f*bz*(q1q3 - q0q2);
	wy = 2.0f*bx*(q1q2 - q0q3) + 2.0f*bz*(q0q1 + q2q3);
	wz = 2.0f*bx*(q0q2 + q1q3) + 2.0f*bz*(0.5f - q1q1 - q2q2);  
	
	/* 
	 * error is sum of cross product between reference direction 
	 * of fields and direction measured by sensors 
	 */
	ex = (ay*vz - az*vy) + (my*wz - mz*wy);
	ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
	ez = (ax*vy - ay*vx) + (mx*wy - my*wx);

	/* PI */
	if(ex != 0.0f && ey != 0.0f && ez != 0.0f)
	{
		exInt = exInt + ex * Ki * halfT;
		eyInt = eyInt + ey * Ki * halfT;	
		ezInt = ezInt + ez * Ki * halfT;
		
		gx = gx + Kp*ex + exInt;
		gy = gy + Kp*ey + eyInt;
		gz = gz + Kp*ez + ezInt;
	}
	
	tempq0 = q0 + (-q1*gx - q2*gy - q3*gz) * halfT;
	tempq1 = q1 + (q0*gx + q2*gz - q3*gy) * halfT;
	tempq2 = q2 + (q0*gy - q1*gz + q3*gx) * halfT;
	tempq3 = q3 + (q0*gz + q1*gy - q2*gx) * halfT;  

	/* normalise quaternion */
	norm = inv_sqrt(tempq0*tempq0 + tempq1*tempq1 + tempq2*tempq2 + tempq3*tempq3);
	q0 = tempq0 * norm;
	q1 = tempq1 * norm;
	q2 = tempq2 * norm;
	q3 = tempq3 * norm;
}

/**
	* @brief  update imu attitude
  * @param  
	* @retval 
  * @usage  call in main() function
	*/
void imu_attitude_update(void)
{
	/* yaw    -pi----pi */
	imu.yaw = -atan2(2*q1*q2 + 2*q0*q3, -2*q2*q2 - 2*q3*q3 + 1)* 57.3; 
	/* pitch  -pi/2----pi/2 */
	imu.pit = -asin(-2*q1*q3 + 2*q0*q2)* 57.3;   
	/* roll   -pi----pi  */	
	imu.rol =  atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1)* 57.3;
}


void IMU_Init(void)
{
	//SPI通讯 初始化
	SPI5_Config();	
	//mpu陀螺仪 初始化
	mpu_device_init();	
	//气压计初始化
	bmp280Init();	
	//四元数 初始化，mpu陀螺仪需要
	init_quaternion();
}

void IMU_Date_Get(float*yaw,float*pitch,float*roll)
{
		mpu_get_data();
		imu_ahrs_update();
		imu_attitude_update();
		*yaw = imu.yaw;
		*pitch = imu.pit;
		*roll = imu.rol;
}

void IMU_Tem_Get(float* IMU_Tem)
{
	mpu_get_data();
	*IMU_Tem = imu.temp;
}

void IMU_Old_Data(int16_t* IMU_Acce,int16_t* IMU_Gyro,int16_t* IMU_Magn)
{
	mpu_get_data();
	IMU_Acce[0] = mpu_data.ax;
	IMU_Acce[1] = mpu_data.ay;
	IMU_Acce[2] = mpu_data.az;
	IMU_Magn[0] = mpu_data.mx;
	IMU_Magn[1] = mpu_data.my;
	IMU_Magn[2] = mpu_data.mz;
	IMU_Gyro[0] = mpu_data.gx;
	IMU_Gyro[1] = mpu_data.gy;
	IMU_Gyro[2] = mpu_data.gz;
}

void Altitude_Data_Get(float* Altitude)
{
	mpu_get_data();
	*Altitude = altitude;
}


