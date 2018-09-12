/*
 * uart.h
 *
 * Created: 29.08.2018 14:23:44
 *  Author: EdvardOlaf
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "utilities.h"
#include "config.h"


void uart_init();

uint8_t uart_transmit(unsigned char data);

uint8_t uart_recive();

bool uart_is_ready_read() ;



#endif /* UART_H_ */