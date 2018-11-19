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

//Initilize the speaker using Timer 4 and port PH3
void speaker_init();

//Set frequency of note in hertz
void speaker_set_hz(uint16_t hz);

//Turn of speaker
void speaker_off();

//Turn off speaker
void speaker_on();

//Convert frequency to value needed in pwm top register
uint16_t hz_to_timer_top(uint16_t hz);
#endif /* speaker_H_ */