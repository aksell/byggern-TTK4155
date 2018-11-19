/*
 * uart.h
 *
 * Created: 29.08.2018 14:23:44
 *  Author: EdvardOlaf
 */

#ifndef UART_H_
#define UART_H_
#include "config.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "utilities.h"

// Initialize uart communication
void uart_init();

// Transmit 1 byte of data over uart
uint8_t uart_transmit(unsigned char data);

// Reads the uart buffer
uint8_t uart_recive();

// Checks that the uart is has something in the recive buffer
bool uart_is_ready_read();

// Enables the printf to use uart
static FILE uart_stream =
    FDEV_SETUP_STREAM(uart_transmit, uart_recive, _FDEV_SETUP_RW);

#endif /* UART_H_ */