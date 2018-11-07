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
		//printf("Can\r\n");
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
				message.data[0]*=-1;
				//printf("Joy value:	%i \n\r",(int8_t)message.data[0]);
				//dc_motor_set_speed((int8_t)message.data[0]);
				dc_motor_set_refference_possition((int8_t)message.data[0]);
				break;
			case CAN_SLIDER:
				{
					
				
				uint16_t slider_percent;
				slider_percent = message.data[0]*100/255;
				if(slider_percent > 100){
					slider_percent = 100;
				}
				//printf("Slider value:	%d \n\r",slider_percent);
				timer_fast_pwm_duty_cycle(slider_percent);
				break;
				}
			default:
				break;
		}
		message_pending = !CAN_buffer_empty();
	}
}



