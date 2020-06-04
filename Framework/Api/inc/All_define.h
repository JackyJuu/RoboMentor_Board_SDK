#ifndef __ALL_DEFINE_H__
#define __ALL_DEFINE_H__
#include "stm32f4xx.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


//LED
#define RED_LED_ON()      GPIO_ResetBits(GPIOE, GPIO_Pin_11)
#define RED_LED_OFF()     GPIO_SetBits(GPIOE, GPIO_Pin_11)
#define RED_LED_TOGGLE()      GPIO_ToggleBits(GPIOE, GPIO_Pin_11)

#define GREEN_LED_ON()            GPIO_ResetBits(GPIOF, GPIO_Pin_14)
#define GREEN_LED_OFF()           GPIO_SetBits(GPIOF, GPIO_Pin_14)
#define GREEN_LED_TOGGLE()        GPIO_ToggleBits(GPIOF, GPIO_Pin_14)

#define BLUE_LED_ON()            GPIO_ResetBits(GPIOH, GPIO_Pin_13)
#define BLUE_LED_OFF()           GPIO_SetBits(GPIOH, GPIO_Pin_13)
#define BLUE_LED_TOGGLE()        GPIO_ToggleBits(GPIOH, GPIO_Pin_13)

//USER_IO
#define USER_IO_PE3_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define USER_IO_PH14_READ  GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_14)
#define USER_IO_PE9_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)
#define USER_IO_PH15_READ  GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_15)
#define USER_IO_PE10_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)
#define USER_IO_PI1_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_1)
#define USER_IO_PE12_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)
#define USER_IO_PI3_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_3)
#define USER_IO_PF2_READ  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)
#define USER_IO_PI4_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_4)
#define USER_IO_PF11_READ  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_11)
#define USER_IO_PI8_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_8)
#define USER_IO_PF12_READ  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_12)
#define USER_IO_PI9_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_9)
#define USER_IO_PF13_READ  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13)
#define USER_IO_PI10_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_10)
#define USER_IO_PF15_READ  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_15)
#define USER_IO_PI11_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_11)

#define USER_IO_PE3_HIGH()     GPIO_ResetBits(GPIOE, GPIO_Pin_3)
#define USER_IO_PE3_LOW()     	GPIO_SetBits(GPIOE, GPIO_Pin_3)
#define USER_IO_PE3_TOGGLE()   GPIO_ToggleBits(GPIOE, GPIO_Pin_3)

#define USER_IO_PH14_HIGH()     GPIO_ResetBits(GPIOH, GPIO_Pin_14)
#define USER_IO_PH14_LOW()     	GPIO_SetBits(GPIOH, GPIO_Pin_14)
#define USER_IO_PH14_TOGGLE()   GPIO_ToggleBits(GPIOH, GPIO_Pin_14)

#define USER_IO_PE9_HIGH()     GPIO_ResetBits(GPIOE, GPIO_Pin_9)
#define USER_IO_PE9_LOW()     	GPIO_SetBits(GPIOE, GPIO_Pin_9)
#define USER_IO_PE9_TOGGLE()   GPIO_ToggleBits(GPIOE, GPIO_Pin_9)

#define USER_IO_PH15_HIGH()     GPIO_ResetBits(GPIOH, GPIO_Pin_15)
#define USER_IO_PH15_LOW()     	GPIO_SetBits(GPIOH, GPIO_Pin_15)
#define USER_IO_PH15_TOGGLE()   GPIO_ToggleBits(GPIOH, GPIO_Pin_15)

#define USER_IO_PE10_HIGH()     GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define USER_IO_PE10_LOW()     	GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define USER_IO_PE10_TOGGLE()   GPIO_ToggleBits(GPIOE, GPIO_Pin_10)

#define USER_IO_PI1_HIGH()     GPIO_ResetBits(GPIOI, GPIO_Pin_1)
#define USER_IO_PI1_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_1)
#define USER_IO_PI1_TOGGLE()   GPIO_ToggleBits(GPIOI, GPIO_Pin_1)

#define USER_IO_PE12_HIGH()     GPIO_ResetBits(GPIOE, GPIO_Pin_12)
#define USER_IO_PE12_LOW()     	GPIO_SetBits(GPIOE, GPIO_Pin_12)
#define USER_IO_PE12_TOGGLE()   GPIO_ToggleBits(GPIOE, GPIO_Pin_12)

#define USER_IO_PI3_HIGH()     GPIO_ResetBits(GPIOI, GPIO_Pin_3)
#define USER_IO_PI3_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_3)
#define USER_IO_PI3_TOGGLE()   GPIO_ToggleBits(GPIOI, GPIO_Pin_3)

#define USER_IO_PF2_HIGH()     GPIO_ResetBits(GPIOF, GPIO_Pin_2)
#define USER_IO_PF2_LOW()     	GPIO_SetBits(GPIOF, GPIO_Pin_2)
#define USER_IO_PF2_TOGGLE()   GPIO_ToggleBits(GPIOF, GPIO_Pin_2)

#define USER_IO_PI4_HIGH()     GPIO_ResetBits(GPIOI, GPIO_Pin_4)
#define USER_IO_PI4_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_4)
#define USER_IO_PI4_TOGGLE()   GPIO_ToggleBits(GPIOI, GPIO_Pin_4)

#define USER_IO_PF11_HIGH()     GPIO_ResetBits(GPIOF, GPIO_Pin_11)
#define USER_IO_PF11_LOW()     	GPIO_SetBits(GPIOF, GPIO_Pin_11)
#define USER_IO_PF11_TOGGLE()   GPIO_ToggleBits(GPIOF, GPIO_Pin_11)

#define USER_IO_PI8_HIGH()     GPIO_ResetBits(GPIOI, GPIO_Pin_8)
#define USER_IO_PI8_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_8)
#define USER_IO_PI8_TOGGLE()   GPIO_ToggleBits(GPIOI, GPIO_Pin_8)

#define USER_IO_PF12_HIGH()     GPIO_ResetBits(GPIOF, GPIO_Pin_12)
#define USER_IO_PF12_LOW()     	GPIO_SetBits(GPIOF, GPIO_Pin_12)
#define USER_IO_PF12_TOGGLE()   GPIO_ToggleBits(GPIOF, GPIO_Pin_12)

#define USER_IO_PI9_HIGH()     GPIO_ResetBits(GPIOI, GPIO_Pin_9)
#define USER_IO_PI9_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_9)
#define USER_IO_PI9_TOGGLE()   GPIO_ToggleBits(GPIOI, GPIO_Pin_9)

#define USER_IO_PF13_HIGH()     GPIO_ResetBits(GPIOF, GPIO_Pin_13)
#define USER_IO_PF13_LOW()     	GPIO_SetBits(GPIOF, GPIO_Pin_13)
#define USER_IO_PF13_TOGGLE()   GPIO_ToggleBits(GPIOF, GPIO_Pin_13)

#define USER_IO_PI10_HIGH()     GPIO_ResetBits(GPIOI, GPIO_Pin_10)
#define USER_IO_PI10_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_10)
#define USER_IO_PI10_TOGGLE()   GPIO_ToggleBits(GPIOI, GPIO_Pin_10)

#define USER_IO_PF15_HIGH()     GPIO_ResetBits(GPIOF, GPIO_Pin_15)
#define USER_IO_PF15_LOW()     	GPIO_SetBits(GPIOF, GPIO_Pin_15)
#define USER_IO_PF15_TOGGLE()   GPIO_ToggleBits(GPIOF, GPIO_Pin_15)

#define USER_IO_PI11_HIGH()     GPIO_ResetBits(GPIOI, GPIO_Pin_11)
#define USER_IO_PI11_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_11)
#define USER_IO_PI11_TOGGLE()   GPIO_ToggleBits(GPIOI, GPIO_Pin_11)

//PWM_IO
#define PWM_PD12_READ  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)
#define PWM_PD13_READ  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)
#define PWM_PD14_READ  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)
#define PWM_PD15_READ  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)
#define PWM_PH10_READ  GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_10)
#define PWM_PH11_READ  GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_11)
#define PWM_PH12_READ  GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_12)
#define PWM_PI0_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_0)
#define PWM_PA0_READ  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define PWM_PA1_READ  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define PWM_PA2_READ  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define PWM_PA3_READ  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define PWM_PI5_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_5)
#define PWM_PI6_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_6)
#define PWM_PI7_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_7)
#define PWM_PI2_READ  GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_2)

#define PWM_PA8_READ  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define PWM_PA9_READ  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)
#define PWM_PE13_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)
#define PWM_PE14_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)

#define PWM_PA8_HIGH()     GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define PWM_PA8_LOW()     	GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define PWM_PA8_TOGGLE()   GPIO_ToggleBits(GPIOA, GPIO_Pin_8)

#define PWM_PA9_HIGH()     GPIO_ResetBits(GPIOA, GPIO_Pin_9)
#define PWM_PA9_LOW()     	GPIO_SetBits(GPIOA, GPIO_Pin_9)
#define PWM_PA9_TOGGLE()   GPIO_ToggleBits(GPIOA, GPIO_Pin_9)

#define PWM_PE13_HIGH()     GPIO_ResetBits(GPIOE, GPIO_Pin_13)
#define PWM_PE13_LOW()     	GPIO_SetBits(GPIOE, GPIO_Pin_13)
#define PWM_PE13_TOGGLE()   GPIO_ToggleBits(GPIOE, GPIO_Pin_13)

#define PWM_PE14_HIGH()     GPIO_ResetBits(GPIOE, GPIO_Pin_14)
#define PWM_PE14_LOW()     	GPIO_SetBits(GPIOE, GPIO_Pin_14)
#define PWM_PE14_TOGGLE()   GPIO_ToggleBits(GPIOE, GPIO_Pin_14)




#define PWM_PD12_HIGH()     GPIO_ResetBits(GPIOD, GPIO_Pin_12)
#define PWM_PD12_LOW()     	GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define PWM_PD12_TOGGLE()   GPIO_ToggleBits(GPIOD, GPIO_Pin_12)

#define PWM_PD13_HIGH()     GPIO_ResetBits(GPIOD, GPIO_Pin_13)
#define PWM_PD13_LOW()     	GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define PWM_PD13_TOGGLE()   GPIO_ToggleBits(GPIOD, GPIO_Pin_13)

#define PWM_PD14_HIGH()     GPIO_ResetBits(GPIOD, GPIO_Pin_14)
#define PWM_PD14_LOW()     	GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define PWM_PD14_TOGGLE()   GPIO_ToggleBits(GPIOD, GPIO_Pin_14)

#define PWM_PD15_HIGH()     GPIO_ResetBits(GPIOD, GPIO_Pin_15)
#define PWM_PD15_LOW()     	GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define PWM_PD15_TOGGLE()   GPIO_ToggleBits(GPIOD, GPIO_Pin_15)

#define PWM_PH10_HIGH()     GPIO_ResetBits(GPIOH, GPIO_Pin_10)
#define PWM_PH10_LOW()     	GPIO_SetBits(GPIOH, GPIO_Pin_10)
#define PWM_PH10_TOGGLE()   GPIO_ToggleBits(GPIOH, GPIO_Pin_10)

#define PWM_PH11_HIGH()     GPIO_ResetBits(GPIOH, GPIO_Pin_11)
#define PWM_PH11_LOW()     	GPIO_SetBits(GPIOH, GPIO_Pin_11)
#define PWM_PH11_TOGGLE()   GPIO_ToggleBits(GPIOH, GPIO_Pin_11)

#define PWM_PH12_HIGH()     GPIO_ResetBits(GPIOH, GPIO_Pin_12)
#define PWM_PH12_LOW()     	GPIO_SetBits(GPIOH, GPIO_Pin_12)
#define PWM_PH12_TOGGLE()   GPIO_ToggleBits(GPIOH, GPIO_Pin_12)

#define PWM_PI0_HIGH()    	GPIO_ResetBits(GPIOI, GPIO_Pin_0)
#define PWM_PI0_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_0)
#define PWM_PI0_TOGGLE()   	GPIO_ToggleBits(GPIOI, GPIO_Pin_0)

#define PWM_PA0_HIGH()      GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define PWM_PA0_LOW()     	GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define PWM_PA0_TOGGLE()    GPIO_ToggleBits(GPIOA, GPIO_Pin_0)

#define PWM_PA1_HIGH()      GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define PWM_PA1_LOW()     	GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define PWM_PA1_TOGGLE()    GPIO_ToggleBits(GPIOA, GPIO_Pin_1)

#define PWM_PA2_HIGH()      GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define PWM_PA2_LOW()     	GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define PWM_PA2_TOGGLE()    GPIO_ToggleBits(GPIOA, GPIO_Pin_2)

#define PWM_PA3_HIGH()      GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define PWM_PA3_LOW()     	GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define PWM_PA3_TOGGLE()    GPIO_ToggleBits(GPIOA, GPIO_Pin_3)

#define PWM_PI5_HIGH()    	GPIO_ResetBits(GPIOI, GPIO_Pin_5)
#define PWM_PI5_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_5)
#define PWM_PI5_TOGGLE()    GPIO_ToggleBits(GPIOI, GPIO_Pin_5)

#define PWM_PI6_HIGH()      GPIO_ResetBits(GPIOI, GPIO_Pin_6)
#define PWM_PI6_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_6)
#define PWM_PI6_TOGGLE()    GPIO_ToggleBits(GPIOI, GPIO_Pin_6)

#define PWM_PI7_HIGH()      GPIO_ResetBits(GPIOI, GPIO_Pin_7)
#define PWM_PI7_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_7)
#define PWM_PI7_TOGGLE()   GPIO_ToggleBits(GPIOI, GPIO_Pin_7)

#define PWM_PI2_HIGH()      GPIO_ResetBits(GPIOI, GPIO_Pin_2)
#define PWM_PI2_LOW()     	GPIO_SetBits(GPIOI, GPIO_Pin_2)
#define PWM_PI2_TOGGLE()    GPIO_ToggleBits(GPIOI, GPIO_Pin_2)

//KEY_IO
#define KEY_READ  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)

//BUZZER
#define BUZZER_ON()      		 GPIO_SetBits(GPIOH, GPIO_Pin_6)
#define BUZZER_OFF()     		 GPIO_ResetBits(GPIOH, GPIO_Pin_6)
#define BUZZER_TOGGLE()      GPIO_ToggleBits(GPIOH, GPIO_Pin_6)

//POWER
#define POWER1_24V_OFF()      GPIO_ResetBits(GPIOH, GPIO_Pin_2)
#define POWER1_24V_ON()     	GPIO_SetBits(GPIOH, GPIO_Pin_2)

#define POWER2_24V_OFF()      GPIO_ResetBits(GPIOH, GPIO_Pin_4)
#define POWER2_24V_ON()     	GPIO_SetBits(GPIOH, GPIO_Pin_4)

#define POWER3_24V_OFF()      GPIO_ResetBits(GPIOH, GPIO_Pin_3)
#define POWER3_24V_ON()     	GPIO_SetBits(GPIOH, GPIO_Pin_3)

#define POWER4_24V_OFF()      GPIO_ResetBits(GPIOH, GPIO_Pin_5)
#define POWER4_24V_ON()     	GPIO_SetBits(GPIOH, GPIO_Pin_5)

#define POWER_5V_A_OFF()    	GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define POWER_5V_A_ON()    		GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define POWER_5V_A_TOGGLE()  	GPIO_ToggleBits(GPIOA, GPIO_Pin_15)

#define POWER_5V_B_OFF()      GPIO_ResetBits(GPIOB, GPIO_Pin_11)
#define POWER_5V_B_ON()    		GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define POWER_5V_B_TOGGLE()   GPIO_ToggleBits(GPIOB, GPIO_Pin_11)


#endif
