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
#include "oled_menu.h"
#include "interrupts.h"
#include "push_buttons.h"
#include "timer.h"
#include "spi.h"
#include "CAN_controller.h"
#include "CAN_buffer.h"

int main(void)
{
	external_mem_init();
	uart_init();
	joystick_init(false);
	push_buttons_init();
	interrupt_init();
	timer_init();
	spi_init();
	CAN_init();
	CAN_buffer_init();
	
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
	
	
	
	//printf("12346YGFHGF \n");
	//printf("2 \n");
    while (1) 
		{
		
		stdout = &uart_stream;
		CAN_buffer_test_2();
		
		/*
		uint8_t data [3];
		data[0]=2;
		data[1]=2;
		data[2]=3;
		
		uint8_t read_data [3];
		uint8_t * address;
		uint8_t recieved_length;
		CAN_transmit(data,1);
		_delay_ms(100);
		CAN_recive(address,data,recieved_length);
		for (int i = 0;i<1;i++){
			printf("Sending: %d\r\n",data[i]);
			printf("Receiving: %d\r\n", read_data[i]);
			printf("Receiving address: %d\r\n", *address);
			printf("Receiving length: %d\r\n", recieved_length);
		}
		printf("\n");
		/*
		_delay_ms(10);
		if (uart_is_ready_read()){
			uart_test_recieve =  uart_recive();
			//uart_transmit(uart_test_recieve);f
			printf("%c",uart_test_recieve);
			//printf("HEi, %i\r\n", 5);
		*/
		stdout = &oled_stream;
		menu_update();
		push_buttons_poll();
		
		//menu_increment_current_value();
		_delay_ms(5000);
			
		}

	

    
}

