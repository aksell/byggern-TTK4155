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

//Forward declarations of state update functions
void standby_update();
void ingame_update();
void game_over_update();

void state_machine_init() {
	printf("STANDBY\n\r");
	state = STANDBY;
	next_state = STANDBY;
	dc_motor_set_refference_middle();
	dc_motor_controller_enable();
}

void state_machine_update() {
	switch(state) {
		case STANDBY:
		standby_update();
		switch(next_state) {
			case INGAME:
				printf("IN GAME \r\n");
			break;
			default:
				next_state = STANDBY;
			break;
		}
		break;
	
		case INGAME:
		ingame_update();
		switch(next_state) {
			case STANDBY:
				printf("STANDBY\n\r");
			break;
			default:
				next_state = INGAME;
				
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
			case CAN_GAME_OVER:
			printf("end game message\n\r");
			message.address = CAN_GAME_OVER_ACK;
			message.data_size = 0;
			CAN_transmit_message(&message);
			dc_motor_set_refference_middle();
			next_state = STANDBY;
			break;
		
		
			case CAN_START_GAME:
				printf("start game message\n\r");
				message.address = CAN_START_GAME_ACK;
				message.data_size = 0;
				CAN_transmit_message(&message);
				next_state = INGAME;
				break;
				
			case CAN_START_MUSIC:
				printf("Start music message\n\r");
				music_play(message.data[0]);
				break;
			case CAN_START_MUSIC_LOOP:
				printf("start music loop message\n\r");
				music_play_loop(message.data[0]);
				break;
			case CAN_STOP_MUSIC:
				music_reset();
				break;
			case CAN_MOTOR_CALIBRATE:
				dc_motor_controller_dissable();
				dc_motor_calibrate_limits();
				dc_motor_controller_enable();
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
				printf("end game message\n\r");
				message.address = CAN_GAME_OVER_ACK;
				message.data_size = 0;
				CAN_transmit_message(&message);
				dc_motor_set_refference_middle();
				next_state = STANDBY;
				break;
			
			case CAN_START_MUSIC:
				printf("start music message\n\r");
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
				dc_motor_set_refference_ofset(((int16_t)message.data[0]-127)*2);
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
		can_message message;
		message.address = CAN_BALL_SENSOR_TRIGGERED;
		message.data_size = 0;
		CAN_transmit_message(&message);
	}
}
