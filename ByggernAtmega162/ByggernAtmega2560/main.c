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
#include "speaker.h"
#include "music.h"
#include "solenoide.h"
#include "state_machine.h"
int main(void)
{
	servo_init_fast_pwm_3();
	uart_init();
	spi_init();
	CAN_buffer_init();
	CAN_init();
	dac_init();
	timer0_init();
	dc_motor_init();
	ball_sensor_init();
	music_init();
	solenoide_init();
	state_machine_init();
	sei();

	stdout = &uart_stream;
	can_message message;
	
	//music_set_bpm(80);
	//music_play_loop(GOT_MUSIC);
	printf("Hei\n\r");
    while (1) 
	{		
		state_machine_update();
		_delay_ms(10);
	}
}
