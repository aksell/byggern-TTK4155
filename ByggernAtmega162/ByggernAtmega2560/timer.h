/*
 * timer.h
 *
 * Created: 24.10.2018 09:25:06
 *  Author: EdvardOlaf
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "config.h"
#include <avr/io.h>
void timer_init_fast_pwm_0();
void timer_test();
void timer_fast_pwm_duty_cycle(uint16_t per_cent_duty);


#endif /* TIMER_H_ */