/*
 * utilities.c
 *
 * Created: 29.08.2018 17:27:40
 *  Author: akselsl
 */ 

#include "utilities.h"


uint16_t convert_from_8_to_16(uint8_t msB, uint8_t lsB){
	uint16_t data_both = 0x0000;
	data_both = ((uint16_t)msB);
	data_both = data_both << 8;
	data_both |= lsB;
	return data_both;
}
void convert_from_16_to_8(uint16_t data_all, uint8_t * array_data){
	array_data[0] = 0;
	array_data[1] = 0;
	array_data[0] = (data_all >>8) & 0x00ff;
	array_data[1] = data_all & 0x00ff;
	
}