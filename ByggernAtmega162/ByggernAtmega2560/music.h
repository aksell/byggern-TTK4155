/*
 * music.h
 *
 * Created: 05.11.2018 16:49:47
 *  Author: EdvardOlaf
 */ 


#ifndef MUSIC_H_
#define MUSIC_H_

#include "avr/io.h"
#include "config.h"
#include <util/atomic.h>
#include "speaker.h"
#include "utilities.h"

typedef uint16_t Note[2];

void music_init();

void music_timer_init();
void music_set_bpm(uint16_t bpm);
void music_play(Note * melodi);

bool music_is_playing();

void music_test();

#endif /* MUSIC_H_ */