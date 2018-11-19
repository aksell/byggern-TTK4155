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


//Initialize uart in USART0
void uart_init();

//Transmit character over uart
uint8_t uart_transmit(unsigned char data);

//Receive character from uart
uint8_t uart_recive();

//Check if uart is ready
bool uart_is_ready_read() ;

//File stream used for printf()
static FILE uart_stream = FDEV_SETUP_STREAM  (uart_transmit, uart_recive, _FDEV_SETUP_RW);

#endif /* UART_H_ */