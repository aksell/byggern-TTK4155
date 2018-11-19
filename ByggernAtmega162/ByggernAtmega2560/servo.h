/*
 * timer.h
 *
 * Created: 24.10.2018 09:25:06
 *  Author: EdvardOlaf
 */
#ifndef SERVO_H_
#define SERVO_H_
#include "config.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>

#include "dc_motor.h"
#include "uart.h"

// Initialize servo
void servo_init_fast_pwm_3();

// Sets the PWM output on pin 5/PE3
// Expects a value from -128 to 127
void servo_fast_pwm_duty_cycle(int8_t duty);

#endif /* SERVO_H_ */