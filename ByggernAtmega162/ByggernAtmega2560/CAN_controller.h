/*
 * CAN_controller.h
 *
 * Created: 03.10.2018 13:54:03
 *  Author: torbjfug
 */

#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

#include "MCP2515_driver.h"
#include "MCP2515_reg.h"
#include "avr/interrupt.h"
#include "uart.h"
#include <avr/io.h>

#define CAN_MESSAGE_MAX_SIZE 8
#define CAN_ADDRESS_OFFSET 5
#define CAN_ADDRESS_OFFSET_CONSTRUCT_bm 0xffe0
#define CAN_ADDRESS_OFFSET_READ_bm 0x7fff

typedef struct can_message_s {
  uint16_t address;
  uint8_t data_size;
  uint8_t data[CAN_MESSAGE_MAX_SIZE];
} can_message;

#include "CAN_buffer.h"

// Initialize CAN driver
void CAN_init();

// Transmit can message to the CAN bus
void CAN_transmit_message(can_message *message);

// Read message from the CAN driver, through pointer
void CAN_recive_message(can_message *message);

// Test function sending and receiving CAN message
void CAN_test();

#endif /* CAN_CONTROLLER_H_ */