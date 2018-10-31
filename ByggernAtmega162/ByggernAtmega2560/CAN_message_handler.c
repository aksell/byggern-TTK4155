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
/*
		printf("Address:	%d\n\r",message.address);
		printf("Received data:\n\r");
		for(int i = 0; i<message.data_size;i++){
			printf("%d,  ",message.data[i]);
		}
		printf("\n\r");
		*/
		switch (message.address){
			case CAN_JOYSTICK_X:
				//code servo control goes here
				break;
			case CAN_SLIDER:
				dac_write(message.data[0]);
				break;
			default:
				break;
		}
		message_pending = !CAN_buffer_empty();
	}
}



