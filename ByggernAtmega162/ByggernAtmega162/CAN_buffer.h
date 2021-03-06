/*
 * CAN_buffer.h
 *
 * Created: 10.10.2018 09:26:28
 *  Author: torbjfug
 */

#ifndef CAN_BUFFER_H_
#define CAN_BUFFER_H_

#define CAN_BUFFER_SIZE 22

#include <avr/io.h>
#include <util/atomic.h>

#include "CAN_controller.h"
#include "config.h"
#include "uart.h"
#include "utilities.h"

void CAN_buffer_init();

void CAN_buffer_write(can_message *message);

can_message CAN_buffer_read();

uint8_t CAN_buffer_remaining_size();
bool CAN_buffer_empty();
bool CAN_buffer_full();
void CAN_buffer_set_full();

void CAN_buffer_reset();

void CAN_buffer_test();
void CAN_buffer_test_2();

#endif /* CAN_BUFFER_H_ */