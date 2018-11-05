/*
 * slider.h
 *
 * Created: 12.09.2018 17:16:39
 *  Author: akselsl
 */ 


#ifndef SLIDER_H_
#define SLIDER_H_
#include "config.h"
#include "adc.h"

typedef enum slider_side_e{
	SLIDER_RIGHT,
	SLIDER_LEFT
};

volatile uint8_t slider_get(enum slider_side_e slider_side_p);

#endif /* SLIDER_H_ */