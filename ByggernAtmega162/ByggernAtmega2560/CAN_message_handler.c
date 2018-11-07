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
		printf("Can\r\n");
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
				printf("Joy value:	%i \n\r",(int8_t)message.data[0]);
				dc_motor_set_reference_delta_position(message.data[0]);
				dc_motor_PI_controller_update();
				break;
			case CAN_SLIDER:
				printf("Slider value:	%d \n\r",message.data[0]);
				//dac_write(100);
				break;
			default:
				break;
		}
		message_pending = !CAN_buffer_empty();
	}
}



