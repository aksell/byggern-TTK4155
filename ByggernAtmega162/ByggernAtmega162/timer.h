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

void timer1_init();
void timer1_reset();
bool timer1_done();

void timer2_init();
void timer2_reset();
bool timer2_done();




#endif /* TIMER_H_ */