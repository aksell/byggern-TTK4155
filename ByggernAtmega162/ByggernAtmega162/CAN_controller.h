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

 
//Convert 16 bit address to hardware layout of registers in MCP2515
uint16_t CAN_addres_construct(uint16_t number);


//Convert address read from registers of MCP2515 to 16 bit number
uint16_t CAN_addres_read(uint16_t number);


can_message CAN_message_construct(uint16_t address, uint8_t data_size, uint8_t * data);

//Test for transmitting and receiving in loop back mode.
void CAN_test();


#endif /* CAN_CONTROLLER_H_ */