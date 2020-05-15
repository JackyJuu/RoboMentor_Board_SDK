#ifndef __LASER_H__
#define __LASER_H__

void Laser_Config(void);

#define LASER_ON()      GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define LASER_OFF()     GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define LASER_TOGGLE()  GPIO_ToggleBits(GPIOA, GPIO_Pin_15)

#define GUN_ON()      GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define GUN_OFF()     GPIO_ResetBits(GPIOB, GPIO_Pin_11)
#define GUN_TOGGLE()  GPIO_ToggleBits(GPIOB, GPIO_Pin_11)

#endif
