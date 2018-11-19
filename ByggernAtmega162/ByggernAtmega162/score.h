/*
 * score.h
 *
 * Created: 10.11.2018 14:26:54
 *  Author: torbjfug
 */

#ifndef SCORE_H_
#define SCORE_H_

#include "EEPROM.h"
#include "config.h"
#include "oled.h"
#include "timer.h"
#include "utilities.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/atomic.h>
// Initilize  the score timer counter
void score_init();

// Resets the score
void score_reset();

// Starts the score counting
void score_start_counting();

// Stops the score counting
void score_stop_counting();
void score_set(uint8_t score);
void score_increment();
uint8_t score_get();
void score_screen_init();
void score_screen_update();
bool score_is_screen_outdated();
void score_reset_high_score(int dummy_int);
void score_high_score_display_init();

#endif /* SCORE_H_ */