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
	printf("STANDBY\n\r");
	state = STANDBY;
	next_state = STANDBY;
	dc_motor_set_refference_possition_absolute(0);
	timer0_enable();
}

void state_machine_update() {
	switch(state) {
		case STANDBY:
		standby_update();
		switch(next_state) {
			case INGAME:
				//music_reset();
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
				//music_reset();
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
				printf("Start music messgae\n\r");
				music_play(message.data[0]);
				break;
				
			case CAN_START_MUSIC_LOOP:
				printf("start music loop message\n\r");
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
				//printf("start music loop message\n\r");
				music_play_loop(message.data[0]);
				break;
			case CAN_STOP_MUSIC:
				//printf("stop music message\n\r");
				music_reset();
				break;
			case CAN_SOLANOIDE_TRIGGER_MS:
				printf("solenoid trigger message\n\r");
				solenoide_trigger(((uint16_t)message.data[0] << 7) | (uint16_t)message.data[1]);
				break;
			case CAN_SOLANOIDE_TRIGGER_AND_HOLD:
				//printf("solenoid trig and hold message\n\r");
				solenoide_set_position(1);
				break;
			case CAN_SOLANOIDE_RELIASE:
				//printf("solenoid release message\n\r");
				solenoide_set_position(0);
				break;
			case CAN_MOTOR_POS:
				//printf("motor message	%d\n\r",((int16_t)(message.data[0])-127)*2);
				//int16_t pos = ((int16_t)(message.data[0])-127)*2);
				dc_motor_set_refference_possition_absolute(((int16_t)message.data[0]-127)*2);
				break;
			case CAN_SERVO_POS:
				//printf("servo message\n\r");
				servo_fast_pwm_duty_cycle(message.data[0]);
				break;
			default:
			break;
		}
		message_pending = !CAN_buffer_empty();
	}
	dc_motor_update_encoder();
	if(ball_sensor_is_triggered()) {
		printf("Sent ball sensor msg\n\r");
		can_message message;
		message.address = CAN_BALL_SENSOR_TRIGGERED;
		message.data_size = 0;
		CAN_transmit_message(&message);
	}
}
