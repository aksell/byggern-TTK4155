/*
 * joystick.c
 *
 * Created: 12.09.2018 14:52:39
 *  Author: EdvardOlaf
 */ 
#include "joystick.h"

bool lowpass_enabled;
float alpha = 0.3;

volatile int8_t prev_value[2];
volatile int16_t offset_value[2];

void joystick_init(bool lowpass_enable) {
	lowpass_enabled = false;
	prev_value[0] = 0;
	prev_value[1] = 0;
	
	offset_value[0] = adc_read(1);
	offset_value[1] = adc_read(2);
	
	printf("%d %d\n\r", offset_value[0], offset_value[1]);
	
	lowpass_enabled = lowpass_enable;
}

volatile int8_t get_unfiltered_angle(enum joystick_axis_e joystick_axis_p) {
	return (int8_t)((float)((int16_t)(adc_read(joystick_axis_p+1)) - offset_value[joystick_axis_p])*(60.0/128));
}

volatile int8_t joystick_get_angle(enum joystick_axis_e joystick_axis_p) {
	if(lowpass_enabled) {
		prev_value[joystick_axis_p]  = (int8_t)(get_unfiltered_angle(joystick_axis_p)*alpha + prev_value[joystick_axis_p]*(1.0-alpha));
		return prev_value[joystick_axis_p];
	} else {
		return get_unfiltered_angle(joystick_axis_p);
	}
}

