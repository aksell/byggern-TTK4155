/*
 * slider.c
 *
 * Created: 12.09.2018 17:17:08
 *  Author: akselsl
 */ 
#include "slider.h"

volatile uint8_t slider_get(enum slider_side_e slider_side_p) {
	return adc_read(slider_side_p+3);
}