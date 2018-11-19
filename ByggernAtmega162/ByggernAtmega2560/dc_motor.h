/*
 * dc_motor.h
 *
 * Created: 03.11.2018 17:13:24
 *  Author: torbjfug
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "config.h"
#include <avr/io.h>
#include "dac.h"
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "uart.h"
#include "utilities.h"
#include "timer.h"



typedef enum dc_motor_dir_e{
	DC_MOTOR_LEFT,
	DC_MOTOR_RIGHT
}dc_motor_dir;

#define PI_FREQUENZY 20

void dc_motor_init();

//Signed between -255 and 255. Negative for left.
void dc_motor_set_speed(int16_t speed);

//Poll encoder
void dc_motor_update_encoder();

//Return last polled encoder value
int16_t dc_motor_encoder_read();

//Calibration routine for setting the limits of the motor
void dc_motor_calibrate_limits();

//Discrete PI controller
void dc_motor_PI_controller_update();

//Set reference offset from center position. Expects value between -255 and 255
void dc_motor_set_refference_ofset(int16_t pos);

//Set reference to middle
void dc_motor_set_refference_middle();


//Enable motor controller
void dc_motor_controller_dissable();


//Disable motor controller
void dc_motor_controller_enable();

#endif /* DC_MOTOR_H_ */