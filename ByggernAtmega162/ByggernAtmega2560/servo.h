/*
 * timer.h
 *
 * Created: 24.10.2018 09:25:06
 *  Author: EdvardOlaf
 */ 
#define TIMER0_FREQUENZY 60
#define PI_FREQUENZY TIMER0_FREQUENZY

#ifndef TIMER_H_
#define TIMER_H_
#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>


#include "dc_motor.h"

void servo_init_fast_pwm_3();

//Sets the PWM output on pin 5/PE3
//Expects a value from 0 to 255
void servo_fast_pwm_duty_cycle(uint8_t duty);

#endif /* TIMER_H_ */