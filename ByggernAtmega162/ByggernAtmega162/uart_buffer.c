/*
 * uart_buffer.c
 *
 * Created: 17.10.2018 10:15:50
 *  Author: torbjfug
 */ 

#include "uart_buffer.h"

uint8_t buffer[UART_BUFFER_SIZE];
volatile uint8_t uart_head;
volatile uint8_t uart_tail;
bool uart_buffer_full_var;
bool uart_buffer_empty_var;

void uart_buffer_init(){
	uart_head = 0;
	uart_tail = uart_head;
	uart_buffer_full_var = false;
	uart_buffer_empty_var = true;
	for(int i = 0; i<UART_BUFFER_SIZE; i++){
		buffer[i] = 0;
	}
	
}

void uart_buffer_increment_head(){
	uart_head = (uart_head + 1);
	uart_head = uart_head % UART_BUFFER_SIZE;
	if(uart_head == uart_tail){
		uart_buffer_full_var = true;
	}
	else{
		uart_buffer_empty_var = false;
	}
}

void uart_buffer_increment_tail(){
	uart_tail = (uart_tail + 1) % UART_BUFFER_SIZE;
	uart_buffer_full_var = false;
	if(uart_tail == uart_head){
		uart_buffer_empty_var = true;
	}
}
bool uart_buffer_full(){
	return uart_buffer_full_var;
}

void uart_buffer_set_full(){
	uart_buffer_full_var = true;
}

uint8_t uart_buffer_remaining_size(){
	if(uart_buffer_full_var){
		return 0;
	}
	else if (uart_head >= uart_tail) {
		uint8_t val =(UART_BUFFER_SIZE - uart_head + uart_tail);
		
		return val;
	}
	else {
		uint8_t val = uart_tail-uart_head;
		return val;
	}
}


bool uart_buffer_empty(){
	return uart_buffer_empty_var;
}

void uart_buffer_write(uint8_t data){
	if(uart_buffer_full_var){
		buffer[uart_head] = data;
		uart_buffer_increment_tail();
		uart_buffer_increment_head();
	}
	else{
		buffer[uart_head] = data;
		uart_buffer_increment_head();
	}
}



uint8_t uart_buffer_read(){
	uint8_t data;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		data = buffer[uart_tail];
		uart_buffer_increment_tail();
	}
	return data;
}

ISR(USART0_RXC_vect)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		uint8_t data = uart_recive();
		uart_buffer_write(data);
	}
}


void uart_buffer_test(){
	printf("\n\rGje innput no\n\r");
	_delay_ms(5000);
}
