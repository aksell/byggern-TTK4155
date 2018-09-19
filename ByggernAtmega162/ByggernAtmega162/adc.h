/*
 * adc.h
 *
 * Created: 12.09.2018 14:42:29
 *  Author: akselsl
 */ 

#ifndef ADC_H_
#define ADC_H_

#include "config.h"
#include <util/delay.h>
#include "external_mem.h"


volatile uint8_t adc_read(uint8_t channel);



#endif /* ADC_H_ */