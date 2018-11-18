/*
 * timer.h
 *
 * Created: 10.11.2018 15:25:54
 *  Author: EdvardOlaf
 */ 


#ifndef TIMER_H_
#define TIMER_H_


#define TIMER0_FREQUENZY 80
#define PI_FREQUENZY 20
#define TIMER0_POST_SCALER TIMER0_FREQUENZY/PI_FREQUENZY
#include "config.h"
#include <avr/io.h>
#include "dc_motor.h"
#include "uart.h"

void timer0_init();

void timer0_dissable();

void timer0_enable();

#endif /* TIMER_H_ */