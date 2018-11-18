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

void dc_motor_init();

//Signed between -255 and 255. Negative for left.
void dc_motor_set_speed(int16_t speed);

//Poll encoder
void dc_motor_update_encoder();

//Return last polled encoder value
int16_t dc_motor_encoder_read();

//Calubration routine for setting the limits of the motor
void dc_motor_calibrate_limits();
//void dc_motor_set_reference_delta_position(int16_t pos);

//Discrete PI controller
void dc_motor_PI_controller_update();

//Set reference for controller
void dc_motor_set_refference_possition(int16_t pos);


void dc_motor_set_refference_possition_absolute(int16_t pos);

//Force reference to middle
void dc_motor_set_refference_middle();

//void dc_motor_set_dir(dc_motor_dir dir);
#endif /* DC_MOTOR_H_ */