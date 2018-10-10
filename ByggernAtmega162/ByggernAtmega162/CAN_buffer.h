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

#include "config.h"
#include "utilities.h"
#include "CAN_controller.h"



void CAN_buffer_init();
void CAN_buffer_write(can_message *message);
can_message CAN_buffer_read();
bool CAN_buffer_is_empty();

void CAN_buffer_test();

#endif /* CAN_BUFFER_H_ */