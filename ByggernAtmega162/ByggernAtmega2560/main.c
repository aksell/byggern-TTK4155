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

//#include "timer.h"
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
#include "speaker.h"
#include "music.h"

int main(void)
{

	servo_init_fast_pwm_3();
	uart_init();
	spi_init();
	CAN_buffer_init();
	CAN_init();
	dac_init();
	music_init();
	ball_sensor_init();
	sei();
	stdout = &uart_stream;
	can_message message;

    while (1) 
	{	
			_delay_ms(10000);


	}
}
