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
	CAN_init();
	
	dac_init();
	internal_ADC_init();
	dc_motor_init();
	CAN_buffer_init();
	sei();
	stdout = &uart_stream;
	int i = 0;

	
	
	internal_ADC_set_channel(0);
	internal_ADC_start_free_running_mode();

	can_message message;

    while (1) 
	{	
		//Update values from can buss
		//Drive motor from PID reg
		//Read Ball sensor led
		//Update Servo
		//Update solanoide
		
		dc_motor_PI_controller();
		int16_t encoder_data;
		encoder_data = dc_motor_encoder_read();
		printf("Encoder:	%i\n\r",encoder_data);
		_delay_ms(1);
		
;
		printf("ADC0: %i\n\r", internal_ADC_read_free_running_mode());


		_delay_ms(200);


	}
}
