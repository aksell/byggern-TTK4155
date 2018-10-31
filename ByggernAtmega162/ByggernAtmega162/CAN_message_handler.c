/*
 * CAN_message_handler.c
 *
 * Created: 24.10.2018 15:44:53
 *  Author: torbjfug
 */ 
#include "CAN_message_handler.h"

void CAN_message_handler(){
	can_message message;
	bool message_pending = !CAN_buffer_empty();
	while(message_pending){
		message = CAN_buffer_read();
		printf("Address:	%d\n\r",message.address);
		printf("Received data:\n\r");
		for(int i = 0; i<message.data_size;i++){
			printf("%d,  ",message.data[i]);
		}
		printf("\n\r");
		
		switch (message.address){
			case CAN_IR:
				printf("IR-EVENT\n\r");
				ping_pong_score_increment();
				//code for handling IR event
				break;
			default:
				break;
		}
		message_pending = !CAN_buffer_empty();
	}
}



void CAN_joystick_X_transmit(){
	uint8_t	data = joystick_get_percent(JOYSTICK_X);
	can_message message;
	message = CAN_message_construct(CAN_JOYSTICK_X,1,&data);
	CAN_transmit_message(&message);
	
}

void CAN_joystick_Y_transmit(){
	uint8_t	data = joystick_get_percent(JOYSTICK_Y);
	can_message message;
	message = CAN_message_construct(CAN_JOYSTICK_Y,1,&data);
	CAN_transmit_message(&message);
	
}

void CAN_slider_transmit(){
	
	uint8_t	data = slider_get(SLIDER_LEFT);
	can_message message;
	message = CAN_message_construct(CAN_SLIDER,1,&data);
	CAN_transmit_message(&message);
}