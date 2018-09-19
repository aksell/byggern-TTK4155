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
#include "utilities.h"
#include "external_mem.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"


int main(void)
{
	external_mem_init();
	uart_init();
	joystick_init(false);
	oled_init();
	volatile uint8_t *p = 0x1400;

	unsigned char uart_test_recieve;
	//external_mem_test();
	//oled_white_screen();
	//oled_chess();

	stdout = &oled_stream;
	
	printf("1 \n");
	printf("2 \n");
	
    while (1) 
		{
	
		_delay_ms(10);
		if (uart_is_ready_read()){
			uart_test_recieve =  uart_recive();
			//uart_transmit(uart_test_recieve);f
			printf("%c",uart_test_recieve);
			//printf("HEi, %i\r\n", 5);
			
			
			
		}

	}

    
}

