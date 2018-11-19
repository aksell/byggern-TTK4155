/*
 * CAN_buffer.h
 *
 * Created: 10.10.2018 09:26:28
 *  Author: torbjfug
 */ 


#ifndef CAN_BUFFER_H_
#define CAN_BUFFER_H_

#define CAN_BUFFER_SIZE 88


#include <avr/io.h>
#include <util/atomic.h>

#include "config.h"
#include "utilities.h"
#include "CAN_controller.h"
#include "uart.h"

//Circular buffer with FIFO behaviour 

//Initialize CAN buffer
void CAN_buffer_init();

//Write a CAN message to the can buffer
void CAN_buffer_write(can_message *message);

//Returns the firs ellement in the que
can_message CAN_buffer_read();

//Returns number between 0 and CAN_BUFFER_SIZE
uint8_t CAN_buffer_remaining_size();

//Returns 1 if buffer is empty. Zero otherwise
bool CAN_buffer_empty();

//Reset the buffer and delete all data
void CAN_buffer_flush();


//Test function transmitting 3 can messages
void CAN_buffer_test();

#endif /* CAN_BUFFER_H_ */