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
	interrupt_init();
	timer1_init();
	spi_init();
	CAN_init();
	CAN_buffer_init();
	uart_buffer_init();
	
	_delay_ms(500);
	//external_mem_test();

	
	oled_init();
	stdout = &oled_stream;
	oled_menu_init();
	
	state_machine_init();
	interrupt_init();
	sei();
	//stdout = &uart_stream;
	//printf("\n\rInit\n\r");
	
    while (1) 
		{
		state_machine_update();
		//CAN_buffer_test_2();
		//printf("MAin\n\r");
		//stdout = &uart_stream;
		//printf("Hei\n\r");
		//CAN_buffer_test_2();
		//ping_pong_loop();
		//CAN_test();
		//CAN_interrupt_routine();
		/*uint8_t c;
		bool uart_empty;
		uart_empty = uart_buffer_empty();
		while(!uart_empty){
			c = uart_buffer_read();
			printf("%c",c);
			uart_empty = uart_buffer_empty();
		}*/
		
		}

    return 0;
}
