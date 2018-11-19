/*
 * adc.h
 * Driver for ADC0844
 * Created: 12.09.2018 14:42:29
 *  Author: akselsl
 */ 

#ifndef ADC_H_
#define ADC_H_

#include "config.h"
#include <util/delay.h>
#include "external_mem.h"


//Takes a integer from 1 to 4 and returns the analog value of the corresponding channel of the ADC
uint8_t adc_read(uint8_t channel);

#endif /* ADC_H_ */