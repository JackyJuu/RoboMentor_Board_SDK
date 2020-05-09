#ifndef __SD_H__
#define __SD_H__

#include "sd_card.h"
#include "ff.h"
#include "ff_debug.h"

#define USART1_TF_DEBUG 0

void TF_file_delete(char* filename_t);	
void TF_file_add(char* filename_t, char* data);	
void TF_file_read(char* filename_t,char* data);
void TF_file_write(char* filename_t, char* data);


#endif
