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
}slider_t;

//Get slider state
volatile uint8_t slider_get(slider_t slider);

//Poll single slider
void slider_poll(slider_t slider);

//Poll all sliders
void sliders_poll();

#endif /* SLIDER_H_ */