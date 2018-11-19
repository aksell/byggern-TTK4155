/*
 * timer.h
 *
 * Created: 10.11.2018 15:25:54
 *  Author: EdvardOlaf
 */

#ifndef TIMER_H_
#define TIMER_H_

#define TIMER0_FREQUENZY 80
#define TIMER0_POST_SCALER_MAX TIMER0_FREQUENZY / PI_FREQUENZY
#define TIMER0_PRESCALER 1024

#include "config.h"
#include "dc_motor.h"
#include "uart.h"
#include <avr/io.h>

void timer0_init();

void timer0_dissable();

void timer0_enable();

#endif /* TIMER_H_ */