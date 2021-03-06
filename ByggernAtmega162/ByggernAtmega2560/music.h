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
#include "speaker.h"
#include "utilities.h"
#include <util/atomic.h>

typedef uint16_t Note[2];

typedef enum music_e {
  GOT_MUSIC,
  WALLACE_AND_GROMMIT_MUSIC,
  GAME_OVER_MUSIC,
  ONE_MUSIC
} music_t;

void music_init();

// Initialize timer used for timing in music
void music_timer_init();

// Set beats per minute of music
void music_set_bpm(uint16_t bpm);

// Play song once
void music_play(music_t music);

// Play music and loop to start at the end
void music_play_loop(music_t music);

// Stop playing
void music_reset();
bool music_is_playing();
void music_test();

#endif /* MUSIC_H_ */