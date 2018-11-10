/*
 * ping_pong_loop.h
 *
 * Created: 24.10.2018 16:45:42
 *  Author: torbjfug
 */ 


#ifndef PING_PONG_LOOP_H_
#define PING_PONG_LOOP_H_

#include "stdint.h"
#include "utilities.h"
#include "timer.h"
#include "oled_menu.h"


typedef enum game_states_e{
	SETTUP,
	PLAYING,
	GAME_LOST}program_state;

void ping_pong_loop();
void ping_pong_set_state(program_state state);
void ping_pong_score_increment();



#endif /* PING_PONG_LOOP_H_ */