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


int main(void)
{
	external_mem_init();
	uart_init();
	joystick_init(false);
	volatile uint8_t *p = 0x1400;
	

	unsigned char uart_test_recieve;

	//external_mem_test();
    while (1) 
		{
		printf("Joysticks %d ",(joystick_get_angle(JOYSTICK_X)));
		printf("%d ",(joystick_get_angle(JOYSTICK_Y)));
		
		printf("Sliders: %d ",(slider_get(SLIDER_LEFT)));
		printf("%d \n\r", (slider_get(SLIDER_RIGHT)));
		
		
		_delay_ms(100);
		if (uart_is_ready_read()){
			uart_test_recieve =  uart_recive();
			//uart_transmit(uart_test_recieve);f
			printf("h %c",uart_test_recieve);
			//printf("HEi, %i\r\n", 5);
			
			
			
		}

    }
}

