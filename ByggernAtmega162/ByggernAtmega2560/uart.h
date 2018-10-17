/*
 * uart.h
 *
 * Created: 29.08.2018 14:23:44
 *  Author: EdvardOlaf
 */ 


#ifndef UART_H_
#define UART_H_
#include "config.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "utilities.h"



void uart_init();

uint8_t uart_transmit(unsigned char data);

uint8_t uart_recive();

bool uart_is_ready_read() ;

static FILE uart_stream = FDEV_SETUP_STREAM  (uart_transmit, uart_recive, _FDEV_SETUP_RW);

#endif /* UART_H_ */