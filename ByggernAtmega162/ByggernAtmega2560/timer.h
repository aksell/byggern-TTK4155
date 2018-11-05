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

void timer_init_fast_pwm_0();


//Sets the PWM output on pin 5/PE3
//Expects a value from 0 to 100
void timer_fast_pwm_duty_cycle(uint16_t per_cent_duty);

//Init 
void timer0_init();
#endif /* TIMER_H_ */