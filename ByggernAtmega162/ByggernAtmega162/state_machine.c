/*
 * state_machine.c
 *
 * Created: 07.11.2018 18:29:31
 *  Author: torbjfug
 */ 
#include "state_machine.h"

#define SOLENOIDE_TRIGGER_TIME_MS 100

state_t state_machine_state;
state_t state_machine_next;

bool stop_game_ack_recieved;

uint8_t game_music;

void transmit_single_game_music_message(); //Forward 

void state_machine_init(){
	state_machine_state = MENU;
	state_machine_next = MENU;
	game_music = 0;
	stop_game_ack_recieved = false;
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

void transmit_pos_message(){
	uint8_t	data =  slider_get(SLIDER_RIGHT);
	can_message message;
	message = CAN_message_construct(CAN_MOTOR_POS,1,&data);
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
	//printf("A\n\r");
}

void transmit_end_game_message(){
	uint8_t	data = 1;
	can_message message;
	message = CAN_message_construct(CAN_GAME_OVER,0,&data);
	CAN_transmit_message(&message);
}



//State transmit functions


void in_game_CAN_transmit(){
	transmit_solenoide_pos_message();
	transmit_servo_pos_message();
	transmit_pos_message();
}

void display_stats_CAN_transmit(){
	if(!stop_game_ack_recieved){	
		transmit_end_game_message();
	}
}

//State update functions

/*
Poll IO needed for menu navigation
Update oled menu
*/

void menu_state_update(){
	if (timer3_done()){//Check poling frequency for IO
		joystick_poll();
		push_buttons_poll();
		if(!stop_game_ack_recieved){
			transmit_end_game_message();
			printf("A");
		}
		timer3_reset();
	}
	if (timer1_done()){
		joystick_dir_t dir = joystick_get_dir();
		if(dir == UP){
			oled_menu_up();
		}
		else if(dir == DOWN) {
			oled_menu_down();
		}
		else if(dir == LEFT) {
			oled_menu_decrement_current_value();
		}
		else if(dir == RIGHT) {
			oled_menu_increment_current_value();
		}
		if (push_buttons_get_state(PUSH_BUTTON_LEFT)){
			oled_menu_back();	
		}
		else if(push_buttons_get_state(PUSH_BUTTON_RIGHT)){//push button right button for select
			oled_menu_select_item();
		}
		oled_menu_print_current_menu();
		timer1_reset();
	}
}

/*
Poll button while waiting for player to confirm or abort game start
*/
void idle_state_update(){
	if(timer3_done()){
		push_buttons_poll();
		if(push_buttons_get_state(PUSH_BUTTON_LEFT)){
			state_machine_next = MENU;
		}
		transmit_start_game_message();
		timer3_reset();
	}
	if(timer1_done()){
		oled_menu_print_current_menu();
		timer1_reset();
	}
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
	if (timer1_done())
	{	
		if(push_buttons_get_state(0)){
			oled_menu_back();
		}
		oled_menu_set_score(score_get());
		oled_menu_print_current_menu();
		
		timer1_reset();
	}
	
}

void display_stats_update(){
	
	if (timer3_done()){
		push_buttons_poll();
		display_stats_CAN_transmit();
		timer3_reset();
	}
	if(timer1_done()){
		if (push_buttons_get_state(PUSH_BUTTON_LEFT)){
			state_machine_next = MENU;
			oled_menu_back();
		}
		else if(push_buttons_get_state(PUSH_BUTTON_RIGHT)){//push button right button for select
			state_machine_next =MENU;
			oled_menu_back();
		}
		oled_menu_print_current_menu();
		timer1_reset();
	}
}

//State CAN receive functions
void menu_CAN_recieve(){
	volatile can_message message;
	bool buffer_empty = CAN_buffer_empty();
	while (!buffer_empty){
		message = CAN_buffer_read();
		switch(message.address){
			case CAN_GAME_OVER_ACK:
			stop_game_ack_recieved = true;
			break;
			default:
			break;
		}
		buffer_empty = CAN_buffer_empty();
	}
}

void idle_state_CAN_recieve(){
	can_message message;
	bool buffer_empty = CAN_buffer_empty();
	while (!buffer_empty){
		message = CAN_buffer_read();
		switch(message.address){
			case CAN_START_GAME_ACK:
				state_machine_next = IN_GAME;
				break;
			default:
				break;
		}
		printf("%d\n\r",message.address);
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
			default:
				break;
		}
		buffer_empty = CAN_buffer_empty();
	}
}

void display_stats_CAN_recieve(){
	volatile can_message message;
	bool buffer_empty = CAN_buffer_empty();
	while (!buffer_empty){
		message = CAN_buffer_read();
		switch(message.address){
			case CAN_GAME_OVER_ACK:
				stop_game_ack_recieved = true;
				break;
			default:
				break;
		}
		buffer_empty = CAN_buffer_empty();
	}
}

//State transition functions
void sc_menu_to_idle(){
	stdout = &uart_stream;
	printf("IDLE\n\r");
	transmit_start_game_message();
}

void sc_idle_to_in_game(){
	stdout = &uart_stream;
	printf("IN GAME\n\r");
	score_reset();
	transmit_loop_game_music_message();
	score_start_counting();
}

void sc_idle_to_menu(){
	stdout = &uart_stream;
	printf("MENU\n\r");
	score_stop_counting();
	transmit_game_music_stop();
	stop_game_ack_recieved = false;
}

void sc_in_game_to_menu(){
	stdout = &uart_stream;
	printf("MENU\n\r");
	score_stop_counting();
	oled_menu_back();
	stop_game_ack_recieved = false;
	transmit_game_music_stop();
}


void sc_ingame_to_display_stats(){
	stdout = &uart_stream;
	printf("DISPLAY\n\r");
	oled_menu_display_stats();
	score_stop_counting();
	stop_game_ack_recieved = false;
}

void sc_display_stats_to_menu(){
	printf("MENU f disp\n\r");
	stop_game_ack_recieved = false;
}



void state_machine_update(){
	switch (state_machine_state){
		case MENU:
			menu_state_update();
			menu_CAN_recieve();
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
			idle_state_update();
			idle_state_CAN_recieve(); //Wait for ACK from node 2
			
			switch (state_machine_next){
				case MENU:
					sc_idle_to_menu();
				case IN_GAME:
					stdout = &uart_stream;
					sc_idle_to_in_game();
					state_machine_state = IN_GAME;
					break;
				default:
					break;
			}
			break;
		case IN_GAME:
			in_game_update();
			in_game_can_recieve();
			switch (state_machine_next){
				case MENU:
					sc_in_game_to_menu();
					state_machine_state = MENU;
					break;
				case DISPLAY_STATS:
					sc_ingame_to_display_stats();
					state_machine_state = DISPLAY_STATS;
					break;
			}
			break;		
		case DISPLAY_STATS:
			display_stats_CAN_recieve();
			display_stats_update();
			
			switch (state_machine_next){
				case MENU:
					sc_display_stats_to_menu();
					state_machine_state = MENU;
					break;
			}
			break;
		default:
			break;
	}
}

void state_machine_set_in_game(int dummy_int) {
	state_machine_set_next_state(IDLE);	
}