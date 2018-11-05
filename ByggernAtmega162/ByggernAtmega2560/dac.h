/*
 * dac.h
 *
 * Created: 31.10.2018 10:38:15
 *  Author: torbjfug
 */ 


#ifndef DAC_H_
#define DAC_H_

#include "TWI_Master.h"
#include "config.h"
#include "utilities.h"
#include "uart.h"
#include <avr/io.h>

#define	DAC_SLAVE_ADDRES 0x50
#define AD0 0
#define AD1 1
#define AD2 2


void dac_init();
void dac_write(uint8_t data);



#endif /* DAC_H_ */