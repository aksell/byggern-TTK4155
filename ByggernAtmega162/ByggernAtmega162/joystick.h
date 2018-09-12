/*
 * joystick.h
 *
 * Created: 12.09.2018 14:52:09
 *  Author: EdvardOlaf
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "utilities.h"

enum joystick_axis {
	JOYSTICK_X,
	JOYSTICK_Y
};

void joystick_init(bool lowpass_enable);

int8_t joystick_get_angle(joystick_axis joystick_axis_p);

#endif /* JOYSTICK_H_ */