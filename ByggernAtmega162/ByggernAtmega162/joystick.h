/*
 * joystick.h
 *
 * Created: 12.09.2018 14:52:09
 *  Author: EdvardOlaf
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "config.h"
#include "utilities.h"
#include "adc.h"
#include <stdio.h>

typedef enum joystick_axis_e{
	JOYSTICK_X, 
	JOYSTICK_Y};

void joystick_init(bool lowpass_enable);

volatile int8_t joystick_get_angle(enum joystick_axis_e joystick_axis_p);

#endif /* JOYSTICK_H_ */