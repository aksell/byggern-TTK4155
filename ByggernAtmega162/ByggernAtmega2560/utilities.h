/*
 * utilities.h
 *
 * Created: 29.08.2018 17:28:33
 *  Author: akselsl
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "config.h"
#include <avr/io.h>

#define bool uint8_t
#define false 0
#define true 1

uint16_t convert_from_8_to_16(uint8_t msB, uint8_t lsB);
void convert_from_16_to_8(uint16_t data_all, uint8_t * array_data);
int16_t convert_from_2_compliment(uint16_t number);



#endif /* UTILITIES_H_ */