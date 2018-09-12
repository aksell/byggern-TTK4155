/*
 * adc.c
 *
 * Created: 12.09.2018 14:42:12
 *  Author: akselsl
 */ 

#include "adc.h"

volatile uint8_t adc_read(volatile uint8_t channel){
	if (channel == 1 || channel == 2)
	{
		volatile uint8_t *p = ADC_OFFSET;
		*p = channel+3; //prepare ADC for read on channel. Single ended muxmode.
		return  *p;
	}
	else{
		return 0;
	}
		
}