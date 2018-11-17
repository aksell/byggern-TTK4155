/*
 * ByggernAtmega162.c
 *
 * Created: 29.08.2018 13:48:18
 * Author : EdvardOlaf
 */ 

#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>


#include "uart.h"
#include "uart_buffer.h"
#include "utilities.h"
#include "external_mem.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "oled_menu.h"
#include "interrupts.h"
#include "push_buttons.h"
#include "timer.h"
#include "spi.h"
#include "CAN_controller.h"
#include "CAN_buffer.h"
#include "CAN_message_handler.h"
#include "state_machine.h"


int main(void)
{
	external_mem_init();
	uart_init();
	joystick_init(false);
	push_buttons_init();
	interrupt0_init();
	timer1_init();
	spi_init();
	CAN_init();
	CAN_buffer_init();
	uart_buffer_init();
	
	oled_init();
	stdout = &oled_stream;
	oled_menu_init();
	
	state_machine_init();
	sei();
	stdout = &uart_stream;
	printf("Hei tann\n\r");
	timer3_init();
    while (1) 
		{
		//stdout = &uart_stream;
		//printf("An: %i, %i, %i, %i\n\r", adc_read(1), adc_read(2),adc_read(3), adc_read(4));
		//_delay_ms(100);
		state_machine_update();
		/*if (timer3_done()){
			printf("Done\n\r");
			timer3_reset();
		}*/
		
		
		//_delay_ms(100);
		}

    return 0;
}
