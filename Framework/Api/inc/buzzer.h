#ifndef __BUZZER_H__
#define __BUZZER_H__
#include "stm32f4xx.h"

#define DO_LOW 72000000/900/131
#define RE_LOW 72000000/900/147
#define MI_LOW 72000000/900/165
#define FA_LOW 72000000/900/196
#define SO_LOW 72000000/900/176
#define LA_LOW 72000000/900/220
#define SI_LOW 72000000/900/247

#define DO_MIDDLE 72000000/900/262
#define RE_MIDDLE 72000000/900/296
#define MI_MIDDLE 72000000/900/330
#define FA_MIDDLE 72000000/900/349
#define SO_MIDDLE 72000000/900/392
#define LA_MIDDLE 72000000/900/440
#define SI_MIDDLE 72000000/900/494


#define DO_1 72000000/900/260
#define MI_2 72000000/900/340
#define SO_3 72000000/900/400

#define DO_HIGH 72000000/900/523
#define RE_HIGH 72000000/900/587
#define MI_HIGH 72000000/900/659
#define FA_HIGH 72000000/900/698
#define SO_HIGH 72000000/900/784
#define LA_HIGH 72000000/900/880
#define SI_HIGH 72000000/900/988

#define DO_VERY_HIGH 72000000/900/1046
#define RE_VERY_HIGH 72000000/900/1175
#define MI_VERY_HIGH 72000000/900/1318
#define FA_VERY_HIGH 72000000/900/1397
#define SO_VERY_HIGH 72000000/900/1568
#define LA_VERY_HIGH 72000000/900/1760
#define SI_VERY_HIGH 72000000/900/1967

void Buzzer_Init(void);
void RoboMentor_Board_Start_Music(void);

void buzzer_tone(uint16_t psc,int music,int stop);
void buzzer_set(uint16_t psc);
void buzzer_off(void);

void qianyuqianxun_song(void);
void little_star_song(void);

#endif
