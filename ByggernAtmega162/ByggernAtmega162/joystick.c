/*
 * joystick.c
 *
 * Created: 12.09.2018 14:52:39
 *  Author: EdvardOlaf
 */ 
#include "joystick.h"

bool lowpass_enabled;
float alpha = 0.2;

int8_t prev_value[2];

void joystick_init(bool lowpass_enable) {
	lowpass_enabled = false;
	prev_value[0] = joystick_get_angle(0);
	prev_value[1] = joystick_get_angle(1);
	lowpass_enabled = lowpass_enable;
}

int8_t joystick_get_angle(joystick_axis joystick_axis_p) {
	if(lowpass_enabled) {
		return convert_adc_value_to_angle(adc_read(joystick_axis_p))*alpha + prev_value[joystick_axis_p]*(1-alpha);
	} else {
		return convert_adc_value_to_angle(adc_read(joystick_axis_p));
	}
}

int8_t convert_adc_value_to_angle(uint8_t adc_value) {
	return (int8_t)((int16_t) adc_value - 128)/128*60;
}