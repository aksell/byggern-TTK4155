/*
 * ByggernAtmega162.c
 *
 * Created: 29.08.2018 13:48:18
 * Author : EdvardOlaf
 */ 
 #define F_CPU 4915E3
 #define BAUD 9600



#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "uart.h"
#include "utilities.h"
#include "config.h"

int main(void)
{
	DDRA |= 0b1;
	PORTA |= 0b1;
	uart_init();
	unsigned char uart_test_recieve;
    while (1) 
    {
		
			if (uart_is_ready_read()){
			uart_test_recieve =  uart_recive();
			uart_transmit(uart_test_recieve);
			printf("HEi, %i\r\n", 5);
		}

    }
}

