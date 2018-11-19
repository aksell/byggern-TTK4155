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
#include "push_buttons.h"
#include "timer.h"
#include "CAN_controller.h"
#include "CAN_buffer.h"
#include "state_machine.h"
#include "score.h"


int main(void)
{
	external_mem_init();
	uart_init();
	joystick_init(false); //Use joystick without filtering
	push_buttons_init();
	timer1_init();
	timer3_init();
	spi_init();
	CAN_init();
	CAN_buffer_init();
	uart_buffer_init();
	oled_init();
	oled_menu_init();
	state_machine_init();
	score_init();
	sei();
	stdout = &uart_stream;
	
    while (1) 
	{
		state_machine_update();
	}
    return 0;
}
