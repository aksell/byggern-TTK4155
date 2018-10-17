/*
 * uart_buffer.c
 *
 * Created: 17.10.2018 10:15:50
 *  Author: torbjfug
 */ 

#include "uart_buffer.h"

uint8_t buffer[UART_BUFFER_SIZE];
uint8_t head;
uint8_t tail;

void uart_buffer_init(){
	head = 0;
	tail = 0;
	
	for(int i = 0; i < UART_BUFFER_SIZE; i++){
		buffer[i] = 0;
	}
}
void uart_buffer_increment_head(){
	head = (head + 1) % UART_BUFFER_SIZE;
}

void uart_buffer_increment_tail(){
	tail = (tail + 1) % UART_BUFFER_SIZE;
}

void uart_buffer_write(uint8_t data){
	buffer[head] = data;
	uart_buffer_increment_head();
}

uint8_t uart_buffer_read(){
	uint8_t data;
	//ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		data = buffer[tail];
		uart_buffer_increment_tail();	
	//}
	;
	return data;
}

bool uart_buffer_empty(){
	return head == tail;
}

void uart_buffer_test(){
	stdout = &uart_stream;
	uint8_t data[] = {44, 2, 5,12,4};
	for(int i = 0; i< 5; i++){
		uart_buffer_write(data[i]);
	}
	uint8_t r_data;
	while(!uart_buffer_empty()){
		r_data = uart_buffer_read();
		printf("Received: %d \n\r",r_data);
	}
	printf("\n\r");

}