/*
 * uart.c
 *
 * Created: 29.08.2018 14:24:07
 *  Author: EdvardOlaf
 */ 




#include "uart.h"


 
 void uart_init(){
	 
	uint8_t ubrr = F_CPU/16/UART0_BAUD-1;
	 // Set baud rate register
	 UBRR0H = (ubrr >> 8);
	 UBRR0L = ubrr;
	 
	 //Enable UART RX/TX
	 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	 
	 //Set USRC register access and Set 8bit data,
	 UCSR0C = (1<<URSEL0)|(1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
	
	//Link stdio to UART
	//fdevopen(&uart_transmit,&uart_recive);
	
 }
 
 uint8_t uart_transmit(unsigned char data){
	//Wait for UART transmit ready flag
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
	
	return 0;
	
 }

uint8_t uart_recive(){
	
	
	if (uart_is_ready_read()) {
		return UDR0;
	} else {
		return _FDEV_ERR;
	}
}

bool uart_is_ready_read() {
	//Check UART receive ready flag
	return UCSR0A & (1<<RXC0); 
}

