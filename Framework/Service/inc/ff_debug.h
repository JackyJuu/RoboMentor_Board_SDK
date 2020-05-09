/*----------------------------------------------------------------------*/
#ifndef _FF_DEBUG_H
#define _FF_DEBUG_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "stm32f4xx.h"
#include "sd_card.h"
#include "ff.h"

//#define DEBUG

#ifdef DEBUG
#include "sd_card.h"
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

void FR_print_error( FRESULT fresult );
FRESULT scan_files (char* path);
FRESULT scan_files_usb (char* path);

#endif /* _FF_DEBUG_H */
