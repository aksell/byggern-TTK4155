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


#include "uart.h"
#include "utilities.h"
#include "spi.h"
#include "CAN_controller.h"
#include "CAN_buffer.h"

int main(void)
{
	uart_init();
	spi_init();
	CAN_init();
	//CAN_buffer_init();
	stdout = &uart_stream;
	int i = 0;
    while (1) 
	{
		
		printf("Hei Aksel! %i\n\r", i++);
		printf("+----------+\n\r|          |\n\r| /\\    \/\\ |\n\r| \\/    \\/ |\n\r|          |\n\r|  [-=-=-] |\n\r+----------+\n\n\n\n\r");
		CAN_test();
		_delay_ms(500);
	}
}

