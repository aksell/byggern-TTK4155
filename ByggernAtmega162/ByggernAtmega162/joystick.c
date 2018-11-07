/*
 * joystick.c
 *
 * Created: 12.09.2018 14:52:39
 *  Author: EdvardOlaf
 */ 
#include "joystick.h"

#define JOYSTICK_DEAD_ZONE 10

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

volatile int8_t get_unfiltered_percent(joystick_axis joystick_axis_p) {
	return (int8_t)((((int16_t)(adc_read(joystick_axis_p+1)) - offset_value[joystick_axis_p])*100)/128);
	
}

volatile int8_t get_unfiltered_value(joystick_axis joystick_axis_p) {
	int16_t value = adc_read(joystick_axis_p+1) - offset_value[joystick_axis_p];
	if (abs(value) <= JOYSTICK_DEAD_ZONE){
		value = 0;
	}
	if(value > 127){
		value = 127;
	}
	else if(value < -127){
		value = -127;
	}
	printf("Value:	%d\n\r",value);
	return (int8_t)value;
	
}

volatile int8_t joystick_get_percent(joystick_axis joystick_axis_p) {
	if(lowpass_enabled) {
		prev_value[joystick_axis_p]  = (int8_t)(get_unfiltered_percent(joystick_axis_p)*alpha + prev_value[joystick_axis_p]*(1.0-alpha));
		return prev_value[joystick_axis_p];
	} else {
		return get_unfiltered_percent(joystick_axis_p);
	}
}

volatile int8_t joystick_get_value(joystick_axis joystick_axis_p) {
	if(lowpass_enabled) {
		prev_value[joystick_axis_p]  = (get_unfiltered_value(joystick_axis_p)*alpha + prev_value[joystick_axis_p]*(1.0-alpha));
		return prev_value[joystick_axis_p];
		} else {
		return get_unfiltered_value(joystick_axis_p);
	}
}

joystick_dir joystick_get_dir() {
	int8_t x_a = joystick_get_percent(JOYSTICK_X);
	int8_t y_a = joystick_get_percent(JOYSTICK_Y);
	
	if(x_a > 50) return RIGHT;
	if(x_a < -50) return LEFT;
	if(y_a > 50) return UP;
	if(y_a < -50) return DOWN;
	return NEUTRAL;	
}



