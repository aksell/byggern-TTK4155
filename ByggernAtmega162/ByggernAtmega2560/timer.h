/*
 * timer.h
 *
 * Created: 10.11.2018 15:25:54
 *  Author: EdvardOlaf
 */ 


#ifndef TIMER_H_
#define TIMER_H_


#define TIMER0_FREQUENZY 20
#define PI_FREQUENZY TIMER0_FREQUENZY
#include "config.h"
#include <avr/io.h>
#include "dc_motor.h"

void timer0_init();

#endif /* TIMER_H_ */