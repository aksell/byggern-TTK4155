/*
 * ping_pong_loop.c
 *
 * Created: 24.10.2018 16:45:19
 *  Author: torbjfug
 */ 
#include "ping_pong_loop.h"

program_state game_state;
uint8_t score;



void game_init(){
	score = 0;
	game_state = SETTUP;
	timer2_init();
}

void play_game(){
	if(timer2_done()){
		CAN_joystick_transmit();		
		timer2_reset();
	}
	menu_update();
}

void ping_pong_loop(){
	game_init();
	while(1){
		switch (game_state){
			case SETTUP:
				menu_update();
			break;
			
			case PLAYING:
				play_game();
				break;
			case GAME_LOST:
				//Handleost game
				break;
			default:
				break;
		}
	}
}
void ping_pong_score_increment(){
	score += 1;
}

void ping_pong_set_state(program_state state){
	game_state = state;
}