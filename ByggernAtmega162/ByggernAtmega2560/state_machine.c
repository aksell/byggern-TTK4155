/*
 * state_machine.c
 *
 * Created: 07.11.2018 18:29:49
 *  Author: EdvardOlaf
 */ 

#include "state_machine.h"

typedef enum state_e{
	STANDBY,
	INGAME,
	GAME_OVER
} state_t;

state_t state;
state_t next_state;

void standby_update();
void ingame_update();
void game_over_update();

void state_update() {
	switch(state) {
		case STANDBY:
		stanby_update();
		switch(next_state) {
			default:
				state = STANDBY
			break;
		}
	break;
	
	case INGAME
		ingame_update();
		switch(next_state) {
			default:
				state = INGAME
			break;
		}
	break;
	
	case GAME_OVER
		game_over_update();
		switch(next_state) {
			default:
				state = GAME_OVER
			break;
		}
	break;
	default:
		printf("Error: unknown state");
	break;
	}
	state = next_state;
}
void standby_update() {
	uint8_t messages_handled = 0;
	can_message message;
	bool message_pending = !CAN_buffer_empty();
	
	while(message_pending){
		if(messages_handled++ > 10) {
			break;
		}
		message = CAN_buffer_read();
		
		switch (message.address){
			case CAN_START_GAME:
				can_message start_game_ack;
				start_game_ack.address = CAN_START_GAME_ACK;
				CAN_transmit_message(&start_game_ack);
				next_state = INGAME;
				break;
				
			case CAN_START_MUSIC:
				music_play(message.data[0]);
				break;
				
			case CAN_START_MUSIC_LOOP:
				music_play_loop(message.data[0]);
				break;
			case CAN_STOP_MUSIC:
				music_reset();
				break;
			default:
				break;
		}
		message_pending = !CAN_buffer_empty();
	}
}

void ingame_update() {
	uint8_t messages_handled = 0;
	can_message message;
	bool message_pending = !CAN_buffer_empty();
	
	while(message_pending){
		if(messages_handled++ > 10) {
			break;
		}
		message = CAN_buffer_read();
		switch (message.address){
			case CAN_GAME_OVER:
				can_message game_over_ack;
				start_game_ack.address = CAN_GAME_OVER_ACK;
				CAN_transmit_message(&game_over_ack);
				next_state = STANDBY;
				break;
			
			case CAN_START_MUSIC:
				music_play(message.data[0]);
				break;
			
			case CAN_START_MUSIC_LOOP:
				music_play_loop(message.data[0]);
				break;
			case CAN_STOP_MUSIC:
				music_reset();
				break;
			case CAN_SOLANOIDE_TRIGGER_MS:
				//Solanoide trigger in ms
				break;
			case CAN_SOLANOIDE_TRIGGER_AND_HOLD:
				//Solanoide Trigger
				break;
			case CAN_SOLANOIDE_RELIASE
				//Solanoide reliase
				break;
			case CAN_MOTOR_DELTA_POS
				dc_motor_set_reference_delta_position(message.data[0]);
				break;
			case CAN_SERVO_POS
				servo_fast_pwm_duty_cycle(message.data[0]);
				break;
			default:
			break;
		}
		message_pending = !CAN_buffer_empty();
	}
	if(ball_sensor_is_triggered()) {
		can_message solenoid_message;
		solenoid_message.address = CAN_BALL_SENSOR_TRIGGERED;
		CAN_transmit_message(&solenoid_message);
	}
}

void game_over_update() {
	//Read_CAN_buffer
	//Send Game over status
}