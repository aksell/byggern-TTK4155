/*
 * ping_pong_loop.c
 *
 * Created: 24.10.2018 16:45:19
 *  Author: torbjfug
 */ 
#include "ping_pong_loop.h"

program_state game_state;
uint8_t score;



void ping_pong_init(){
	score = 0;
	game_state = PLAYING;
	timer2_init();
}

void play_game(){
	if(timer1_done()){
		CAN_joystick_X_transmit();	
		CAN_slider_transmit();	
		timer1_reset();

	}
	//menu_update();
}

void ping_pong_loop(){
	ping_pong_init();
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
		CAN_message_handler();
		}
	}
}
void ping_pong_score_increment(){
	score += 1;
}

void ping_pong_set_state(program_state state){
	game_state = state;
}