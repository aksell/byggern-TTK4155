/*
 * uart_buffer.h
 *
 * Created: 17.10.2018 10:16:05
 *  Author: torbjfug
 */ 


#ifndef UART_BUFFER_H_
#define UART_BUFFER_H_

#include <util/atomic.h>
#include <avr/io.h>

#include "uart.h"
#include "utilities.h"
#include "config.h"


#define UART_BUFFER_SIZE 32

//Initialize the uart ring buffer
void uart_buffer_init();

//Write 1 byte to the uart buffer
void uart_buffer_write(uint8_t data);

//Reads the oldest message of the uart buffer
uint8_t uart_buffer_read();

//Returns true if buffer is empty
bool uart_buffer_empty();

//Returns true if buffer is full
bool uart_buffer_full();

//Buffer test
void uart_buffer_test();






#endif /* UART_BUFFER_H_ */