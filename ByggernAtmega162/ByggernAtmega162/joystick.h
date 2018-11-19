/*
 * joystick.h
 *
 * Created: 12.09.2018 14:52:09
 *  Author: EdvardOlaf
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "adc.h"
#include "config.h"
#include "uart.h"
#include "utilities.h"
#include <stdio.h>

typedef enum joystick_axis_e { JOYSTICK_X, JOYSTICK_Y } joystick_axis_t;

typedef enum joystick_dir_e { UP, DOWN, RIGHT, LEFT, NEUTRAL } joystick_dir_t;

// Init the the joystick, if lowpass_enable the value of the joystick will be
// filtered
void joystick_init(bool lowpass_enable);

// Poles and stores the joystick position
void joystick_poll();

// Returns a number between -100 to 100 indicating the joystick position
volatile int8_t joystick_get_percent(joystick_axis_t joystick_axis_p);

// Returns a number between -127 to 127 indicating the joystick position
volatile int8_t joystick_get_value(joystick_axis_t joystick_axis_p);

// Returns a the joystick direction
joystick_dir_t joystick_get_dir();

#endif /* JOYSTICK_H_ */