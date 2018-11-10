/*
 * speaker.h
 *
 * Created: 05.11.2018 11:47:10
 *  Author: EdvardOlaf
 */ 


#ifndef SPEAKER_H_
#define SPEAKER_H_

#include "avr/io.h"
#include <util/atomic.h>
#include "config.h"

void speaker_init();

void speaker_set_hz(uint16_t hz);
void speaker_off();
void speaker_on();
uint16_t hz_to_timer_top(uint16_t hz);
#endif /* speaker_H_ */