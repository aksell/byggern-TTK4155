/*
 * state_machine.c
 *
 * Created: 07.11.2018 18:29:49
 *  Author: EdvardOlaf
 */ 
#include "state_machine.h"

typedef enum state_e{
	STANDBY,
	INGAME
} state_t;

state_t state;
state_t next_state;

void standby_update();
void ingame_update();
void game_over_update();

void state_machine_init() {
	state = STANDBY;	
}

void state_machine_update() {
	switch(state) {
		case STANDBY:
		standby_update();
		switch(next_state) {
			case INGAME:
				music_reset();
			break;
			default:
				state = STANDBY;
			break;
		}
		break;
	
		case INGAME:
		ingame_update();
		switch(next_state) {
			case STANDBY:
				music_reset();
			break;
			default:
			state = INGAME;
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
				message.address = CAN_START_GAME_ACK;
				CAN_transmit_message(&message);
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
				message.address = CAN_GAME_OVER_ACK;
				CAN_transmit_message(&message);
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
				solenoide_trigger(((uint16_t)message.data[0] << 7) | (uint16_t)message.data[1]);
				break;
			case CAN_SOLANOIDE_TRIGGER_AND_HOLD:
				solenoide_set_position(1);
				break;
			case CAN_SOLANOIDE_RELIASE:
				solenoide_set_position(0);
				break;
			case CAN_MOTOR_POS:
				dc_motor_set_refference_possition(message.data[0]);
				break;
			case CAN_SERVO_POS:
				servo_fast_pwm_duty_cycle(message.data[0]);
				break;
			default:
			break;
		}
		message_pending = !CAN_buffer_empty();
	}
	dc_motor_update_encoder();
	if(ball_sensor_is_triggered()) {
		can_message solenoid_message;
		solenoid_message.address = CAN_BALL_SENSOR_TRIGGERED;
		CAN_transmit_message(&solenoid_message);
	}
}
