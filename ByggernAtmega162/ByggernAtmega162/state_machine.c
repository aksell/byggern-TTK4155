/*
 * state_machine.c
 *
 * Created: 07.11.2018 18:29:31
 *  Author: torbjfug
 */ 
#include "state_machine.h"

typedef enum states_e {
	MENU,
	IDLE,
	IN_GAME,
	DISPLAY_STATS
}state_t;

state_t state_machine_state;
state_t state_machine_next;




void state_machine_init(){
	state_machine_state = MENU;
	state_machine_next = MENU;
	timer3_init();
}

void state_machine_set_next_state(state_t next_state){
	state_machine_next = next_state;
}


//CAN message transmissions
void transmit_delta_pos_message(){
	uint8_t	data = joystick_get_percent(JOYSTICK_X);
	can_message message;
	message = CAN_message_construct(CAN_MOTOR_DELTA_POS,1,&data);
	CAN_transmit_message(&message);
}



void transmit_servo_pos_message(){
	uint8_t	data = slider_get(SLIDER_LEFT);
	can_message message;
	message = CAN_message_construct(CAN_SERVO_POS,1,&data);
	CAN_transmit_message(&message);
}

void transmit_solenoide_pos_message(){
	//TO BE IMPLEMENTED
}

void transmit_start_game_message(){
	uint8_t	data = 1;
	can_message message;
	message = CAN_message_construct(CAN_SERVO_POS,1,&data);
	CAN_transmit_message(&message);
}


/*
Poll IO needed for menu navigation
Update oled menu
*/

void menu_state_update(){
	if (timer3_done()){//Check poling frequency for IO
		joystick_poll();
		push_buttons_poll();
		timer3_reset();	
	}
	oled_menu_update();
}

//State transmit functions

void in_game_CAN_transmit(){
	transmit_solenoide_pos_message();
	transmit_servo_pos_message();
	transmit_delta_pos_message();
}

//State update functions

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
	//UPDATE SCORE
}

//State CAN recieve functions
void idle_state_CAN_recieve(){
	can_message message;
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
	can_message message;
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
	
}

sc_idle_to_display_stats(){
	
}


void sc_in_game_to_menu(){
	
}

void sc_ingame_to_display_stats(){
	
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
					//game abort logic
					state_machine_state = MENU;
					break;
				case DISPLAY_STATS:
					sc_ingame_to_display_stats();
					state_machine_state = DISPLAY_STATS;
					break;
			}		
		case DISPLAY_STATS:
			//Display stats
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

