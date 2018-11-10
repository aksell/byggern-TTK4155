/*
 * timer.h
 *
 * Created: 26.09.2018 15:43:28
 *  Author: torbjfug
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "config.h"
#include <avr/io.h>

#include "utilities.h"

void timer0_init();
void timer0_enable();
void timer0_dissable();


void timer1_init();
void timer1_reset();
bool timer1_done();

void timer3_init();
void timer3_reset();
bool timer3_done();




#endif /* TIMER_H_ */