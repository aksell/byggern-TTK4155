/*
 * MCP2515_driver.h
 *
 * Created: 03.10.2018 11:04:56
 *  Author: EdvardOlaf
 */ 


#ifndef MCP2515_DRIVER_H_
#define MCP2515_DRIVER_H_


#include "spi.h"
#include <avr/io.h>
#include "MCP2515_reg.h"

void MCP2515_read(uint8_t address, uint8_t  * data, uint8_t data_size);
void MCP2515_write(uint8_t address, const uint8_t * data, uint8_t data_size);
void MCP2515_rqt_send(uint8_t TXBn_mask);
uint8_t MCP2515_read_status();

//Modifies a register in MCP2515 with a mask that spesifies witch bits that can be edited
void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void MCP2515_reset();


#endif /* MCP2515_DRIVER_H_ */