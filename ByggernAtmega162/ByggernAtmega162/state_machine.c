/*
 * state_machine.c
 *
 * Created: 07.11.2018 18:29:31
 *  Author: torbjfug
 */ 
#include "state_machine.h"

#define SOLENOIDE_TRIGGER_TIME_MS 500

state_t state_machine_state;
state_t state_machine_next;

uint8_t game_music;

void transmit_single_game_music_message(); //Forward 

void state_machine_init(){
	state_machine_state = MENU;
	state_machine_next = MENU;
	game_music = 0;
	timer3_init();
}

void state_machine_set_next_state(state_t next_state){
	state_machine_next = next_state;
}

void state_machine_set_game_music(uint8_t song){
	game_music = song;
	transmit_single_game_music_message();
}

//CAN message transmissions
void transmit_single_game_music_message(){
	can_message message;
	message = CAN_message_construct(CAN_START_MUSIC,1,&game_music);
	CAN_transmit_message(&message);
}
void transmit_loop_game_music_message(){
	can_message message;
	message = CAN_message_construct(CAN_START_MUSIC_LOOP,1,&game_music);
	CAN_transmit_message(&message);
}

void transmit_game_music_stop(){
	can_message message;
	message = CAN_message_construct(CAN_STOP_MUSIC,1,&game_music);
	CAN_transmit_message(&message);
}

void transmit_delta_pos_message(){
	uint8_t	data =  slider_get(SLIDER_LEFT);
	can_message message;
	message = CAN_message_construct(CAN_MOTOR_DELTA_POS,1,&data);
	CAN_transmit_message(&message);
}



void transmit_servo_pos_message(){
	uint8_t	data = joystick_get_percent(JOYSTICK_X);
	can_message message;
	message = CAN_message_construct(CAN_SERVO_POS,1,&data);
	CAN_transmit_message(&message);
}

void transmit_solenoide_pos_message(){
	if(push_buttons_get_state(PUSH_BUTTON_RIGHT)){
		uint16_t trigger_time = SOLENOIDE_TRIGGER_TIME_MS;
		uint8_t data[2];
		convert_from_16_to_8(trigger_time,data);
		can_message message;
		message = CAN_message_construct(CAN_SOLANOIDE_TRIGGER_MS,2,data);
		CAN_transmit_message(&message);
	}
}

void transmit_start_game_message(){
	uint8_t	data = 1;
	can_message message;
	message = CAN_message_construct(CAN_START_GAME,1,&data);
	CAN_transmit_message(&message);
}






//State transmit functions

void in_game_CAN_transmit(){
	transmit_solenoide_pos_message();
	transmit_servo_pos_message();
	transmit_delta_pos_message();
}

//State update functions

/*
Poll IO needed for menu navigation
Update oled menu
*/

void menu_state_update(){
	if (timer1_done()){//Check poling frequency for IO
		joystick_poll();
		push_buttons_poll();
		timer3_reset();
	}
	oled_menu_update();
}

/*
Poll button while waiting for player to confirm or abort game start
*/
void idle_state_update(){
	if(timer3_done()){
		push_buttons_poll();
	}
	oled_menu_update();
}

/*
Poll user input for game
NEED TO ADD SCORE MODULE
*/
void in_game_update(){
	if (timer3_done()){//Check poling frequency for IO
		joystick_poll();
		push_buttons_poll();
		sliders_poll();
		in_game_CAN_transmit();
		timer3_reset();
	}
	oled_menu_update();
}

//State CAN receive functions
void idle_state_CAN_recieve(){
	volatile can_message message;
	bool buffer_empty = CAN_buffer_empty();
	while (!buffer_empty){
		message = CAN_buffer_read();
		switch(message.address){
			case CAN_START_GAME_ACK:
				state_machine_next = IN_GAME;
				break;
			case CAN_GAME_OVER_ACK:
				state_machine_next = DISPLAY_STATS;
				break; 
			default:
				break;
		}
		buffer_empty = CAN_buffer_empty();
	}
}

void in_game_can_recieve(){
	volatile can_message message;
	bool buffer_empty = CAN_buffer_empty();
	while (!buffer_empty){
		message = CAN_buffer_read();
		switch(message.address){
			case CAN_BALL_SENSOR_TRIGGERED:
				state_machine_next = DISPLAY_STATS;
				break;
			case CAN_GAME_OVER:
				state_machine_next = MENU;
				break;
			default:
				break;
		}
		buffer_empty = CAN_buffer_empty();
	}
}

//State transition functions
void sc_menu_to_idle(){
	transmit_start_game_message();
}

void sc_idle_to_in_game(){
	score_reset();
	transmit_loop_game_music_message();
	score_start_counting();
}

void sc_idle_to_display_stats(){
	oled_menu_display_stats();
}


void sc_in_game_to_menu(){
	score_stop_counting();
	transmit_game_music_stop();
}


void sc_ingame_to_idle(){
	score_stop_counting();
}

void sc_display_stats_to_menu(){
	
}



void state_machine_update(){
	switch (state_machine_state){
		case MENU:
			menu_state_update();
			switch (state_machine_next){
				case IDLE:
					sc_menu_to_idle();
					state_machine_state = IDLE;
					break;
				default:
					break;
			}
			break;
		case IDLE:
			idle_state_CAN_recieve(); //Wait for ACK from node 2
			switch (state_machine_next){
				case IN_GAME:
					sc_idle_to_in_game();
					state_machine_state = IN_GAME;
					break;
				case DISPLAY_STATS:
					sc_idle_to_display_stats();
					state_machine_state = DISPLAY_STATS;
				default:
					break;
			}
		case IN_GAME:
			in_game_update();
			in_game_can_recieve();
			switch (state_machine_next){
				case MENU:
					sc_in_game_to_menu();
					state_machine_state = MENU;
					break;
				case IDLE:
					sc_ingame_to_idle();
					state_machine_state = IDLE;
					break;
			}		
		case DISPLAY_STATS:
			oled_menu_update();
			switch (state_machine_next){
				case MENU:
					sc_display_stats_to_menu();
					state_machine_state = MENU;
					break;
			}
		default:
			break;
	}
}

