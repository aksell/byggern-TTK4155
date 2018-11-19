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

#define	DAC_SLAVE_ADDRES 0x28

//Initialize external digital to analog converter
void dac_init();

//Write data to the output of the dac
void dac_write(uint8_t data);



#endif /* DAC_H_ */