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

void uart_buffer_init();
void uart_buffer_write(uint8_t data);
uint8_t uart_buffer_read();

void uart_buffer_test();

bool CAN_buffer_empty();
bool CAN_buffer_full();
void CAN_buffer_set_full();





#endif /* UART_BUFFER_H_ */