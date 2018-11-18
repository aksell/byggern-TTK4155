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
#include <stdio.h>
#include "oled.h"
#include "utilities.h"
//Initilize  the score timer counter
void score_init();

//Resets the score
void score_reset();

//Starts the score counting
void score_start_counting();

//Stops the score counting
void score_stop_counting();
void score_set(uint8_t score);
void score_increment();
uint8_t score_get();
void score_screen_init();
void score_screen_update();
bool score_is_screen_outdated();
#endif /* SCORE_H_ */