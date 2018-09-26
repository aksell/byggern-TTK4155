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

void timer_init();
void timer_reset();
bool timer_done();




#endif /* TIMER_H_ */