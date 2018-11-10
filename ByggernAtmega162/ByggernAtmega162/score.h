/*
 * score.h
 *
 * Created: 10.11.2018 14:26:54
 *  Author: torbjfug
 */ 


#ifndef SCORE_H_
#define SCORE_H_

#include "config.h"
#include "timer.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

void score_init();
void score_reset();
void score_start_counting();
void score_stop_counting();
void score_set(uint8_t score);
void score_increment();
uint8_t score_get();



#endif /* SCORE_H_ */