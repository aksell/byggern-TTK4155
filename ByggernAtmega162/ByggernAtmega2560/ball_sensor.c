/*
 * ball_sensor.c
 *
 * Created: 07.11.2018 18:09:56
 *  Author: EdvardOlaf
 */ 

#include "ball_sensor.h"

#define BALL_SENSOR_CH 0

void ball_sensor_init() {
	internal_ADC_init();
	internal_ADC_set_channel(0);
	internal_ADC_start_free_running_mode();
}

void ball_sensor_is_triggered() {
	return internal_ADC_read_free_running_mode() == 0;	
}