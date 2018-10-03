/*
 * MCP2515_driver.c
 *
 * Created: 03.10.2018 11:04:40
 *  Author: EdvardOlaf
 */ 
#define MCP_RESET		0b11000000
#define MCP_READ		0b00000011
#define MCP_WRITE		0b00000010 
#define MCP_RTS( TXBnnn ) (0b10000000 | (TXBnnn))
#define MCP_READ_STATUS	0b10100000
#define MCP_RX_STATUS	0b10110000
#define MCP_BIT_MODIFY	0b00000101

#include "MCP2515_driver.h"

void MCP2515_read(uint8_t address, uint8_t  * data, uint8_t data_size) {
	//CS LOW
	//Send MCP_READ
	//Send 8 bit address
	//Read MISO pin
	//Adress in indremented
	//OPT: read more
	//CS LOW
}

void MCP2515_write(uint8_t address, uint8_t * data, uint8_t data_size) {
	//CS LOW
	//Send MCP_WRITE
	//Send address
	//Send Data
	//OPT: Send more data
	//CS high
}

void MCP2515_rqt_send() {
	//CS_LOW
	//SEND MCP_RTS( TXBn )
	//CS_HIGH
}

uint8_t MCP2515_read_status() {
	//CS_LOW
	//Send MCP_READ_STATUS
	//Read 8bit data
	//CS_low
}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	//CS LOW
	//Send MCP_BIT_MODIFY
	//Send Address
	//Send Mask
	//Send data
	//CS HIGH
}

void MCP2515_reset() {
	//CS LOW
	//Send instruction byte
	//CS HIGH
}