/*
 * CAN_controller.h
 *
 * Created: 03.10.2018 13:54:03
 *  Author: torbjfug
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

#include <avr/io.h>
#include "MCP2515_reg.h"
#include "MCP2515_driver.h"
#include "uart.h"

#define CAN_MESSAGE_MAX_SIZE 8
#define CAN_ADDRESS_OFFSET 5
#define CAN_ADDRESS_OFFSET_CONSTRUCT_bm 0xffe0
#define CAN_ADDRESS_OFFSET_READ_bm 0x7fff

typedef struct can_message_s{
	uint16_t address;
	uint8_t data_size;
	uint8_t data [CAN_MESSAGE_MAX_SIZE];
}can_message;




void CAN_init();

void CAN_transmit_message(can_message* message);
void CAN_recive_message(can_message* message);
uint16_t CAN_addres_construct(uint16_t number);
uint16_t CAN_addres_read(uint16_t number);


void CAN_test();
void CAN_test_2();



#endif /* CAN_CONTROLLER_H_ */