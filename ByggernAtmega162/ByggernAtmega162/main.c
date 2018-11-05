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
	
	_delay_ms(100);
	volatile uint8_t *p = 0x1400;

	unsigned char uart_test_recieve;
	//external_mem_test();
	//oled_white_screen();
	//oled_chess();
	stdout = &oled_stream;
	//stdout = &uart_stream;

	oled_init();
	menu_init();
	
	stdout = &uart_stream;
	interrupt_init();
	
	uint8_t can_data[8];

	can_message message = CAN_message_construct(3,8,can_data);
	printf("\n\rInit\n\r");
	
    while (1) 
		{
		
		//printf("MAin\n\r");
		stdout = &uart_stream;
		//CAN_joystick_transmit();
		CAN_message_handler();
		//CAN_test();
		//CAN_interrupt_routine();
		uint8_t c;
		bool uart_empty;
		uart_empty = uart_buffer_empty();
		while(!uart_empty){
			c = uart_buffer_read();
			printf("%c",c);
			uart_empty = uart_buffer_empty();
		}
		
		
		stdout = &oled_stream;
		menu_update();
		push_buttons_poll();
		_delay_ms(1000);
		stdout = &uart_stream;
			
		}

	

    return 0;
}
