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



int main(void)
{
	external_mem_init();
	uart_init();
	
	unsigned char *p = (unsigned char *) (0x1000);
	
	unsigned char uart_test_recieve;
	
	external_mem_test();
    while (1) 
		{
	
			
			if (uart_is_ready_read()){
			uart_test_recieve =  uart_recive();
			uart_transmit(uart_test_recieve);
			printf("HEi, %i\r\n", 5);
			
			
		}

    }
}

