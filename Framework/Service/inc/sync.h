#ifndef __SYNC_H__
#define __SYNC_H__

void Sync_Config(void);

#define SYNC_ON()      GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define SYNC_OFF()     GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define SYNC_TOGGLE()  GPIO_ToggleBits(GPIOB, GPIO_Pin_14)

#endif
