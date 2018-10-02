/*
 * external_mem.h
 * 
 * Created: 05.09.2018 10:15:43
 *  Author: akselsl
 */ 


#ifndef EXTERNAL_MEM_H_
#define EXTERNAL_MEM_H_
#include "config.h"
#include <avr/io.h>

#define OLED_CMD_OFFSET 0x1000
#define OLED_DATA_OFFSET 0x1200
#define ADC_OFFSET 0x1400
#define SRAM_OFFSET 0x1800


void external_mem_init();
void external_mem_test(void);


#endif /* EXTERNAL_MEM_H_ */