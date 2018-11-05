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

int main(void)
{
	timer_init_fast_pwm_0();
	uart_init();
	internal_ADC_init();

	spi_init();
	CAN_init();
	sei();
	stdout = &uart_stream;
	int i = 0;
	
	
	internal_ADC_set_channel(0);
	internal_ADC_start_free_running_mode();
    while (1) 
	{
		//Update values from canbuss
		//Drive motor from PID reg
		//Read Ball sensor led
		//Update Servo
		//Update solanoide
		
		//printf("ADC_POll: %i\n\r", internal_ADC_read_polling());
		
		internal_ADC_set_channel(0);
			_delay_ms(10);
		printf("ADC0: %i\n\r", internal_ADC_read_free_running_mode());
		internal_ADC_set_channel(1);
		_delay_ms(10);

		printf("ADC1: %i\n\n\r", internal_ADC_read_free_running_mode());
		

		_delay_ms(200);
	}
}
