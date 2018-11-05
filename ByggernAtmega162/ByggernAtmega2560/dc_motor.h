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
#include <util/delay.h>
#include "uart.h"
#include "utilities.h"
#include "timer.h"



typedef enum dc_motor_dir_e{
	DC_MOTOR_LEFT,
	DC_MOTOR_RIGHT
}dc_motor_dir;

void dc_motor_init();
void dc_motor_set_speed(int16_t speed);
int16_t dc_motor_encoder_read();
void dc_motor_calibrate_limits();
void dc_motor_set_refference_possition(int16_t pos);
void dc_motor_PI_controller_update();

#endif /* DC_MOTOR_H_ */