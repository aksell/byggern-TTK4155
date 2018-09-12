/*
 * ByggernAtmega162.c
 *
 * Created: 29.08.2018 13:48:18
 * Author : EdvardOlaf
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "uart.h"
#include "utilities.h"
#include "external_mem.h"



int main(void)
{
	external_mem_init();
	uart_init();
	
	volatile uint8_t *p = 0x1400;
	

	unsigned char uart_test_recieve;

	//external_mem_test();
    while (1) 
		{
		printf("%d ",(adc_read(1)));
		printf("%d \r\n",(adc_read(2)));
		_delay_ms(400);
		if (uart_is_ready_read()){
			uart_test_recieve =  uart_recive();
			//uart_transmit(uart_test_recieve);f
			printf("h %c",uart_test_recieve);
			//printf("HEi, %i\r\n", 5);
			
			
			
		}

    }
}

