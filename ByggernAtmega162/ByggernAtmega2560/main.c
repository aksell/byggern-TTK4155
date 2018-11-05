/*
 * main.c
 *
 * Created: 17.10.2018 09:26:45
 *  Author: EdvardOlaf
 */ 


#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "uart.h"
#include "utilities.h"
#include "spi.h"
#include "CAN_controller.h"
#include "CAN_buffer.h"
#include "CAN_message_handler.h"
#include "internal_ADC.h"
#include "dc_motor.h"
#include "internal_ADC.h"
#include "utilities.h"

int main(void)
{
	timer_init_fast_pwm_0();
	uart_init();
	internal_ADC_init();
	spi_init();
	CAN_buffer_init();
	CAN_init();
	dac_init();
	internal_ADC_init();
	dc_motor_init();
	timer0_init();
	sei();
	
	stdout = &uart_stream;
	printf("Init done\n\r");
	int i = 0;
	can_message message;
	
    while (1) 
	{	
		CAN_message_handler();
		dc_motor_PI_controller_update();
		//CAN_buffer_test_2();
		//Update values from can buss
		//Drive motor from PID reg
		//Read Ball sensor led
		//Update Servo
		//Update solanoide
		//CAN_buffer_test_2();
		//CAN_message_handler();
		/*int16_t encoder_data;
		encoder_data = dc_motor_encoder_read();
		printf("Encoder:	%i\n\r",encoder_data);*/
		
		
		
		
		
		/*bool message_pending = !CAN_buffer_empty();
		while(message_pending){
			message = CAN_buffer_read();
			printf("Address:	%d\n\r",message.address);
			for(int j = 0;j<message.data_size;j++){
				printf("Received:	%d \n\r", message.data[j]);
			}
			message_pending = !CAN_buffer_empty();
		}*/
		
		
		
	}
}
