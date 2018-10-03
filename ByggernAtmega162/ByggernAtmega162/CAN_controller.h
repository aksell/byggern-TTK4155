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

void CAN_init();
uint8_t CAN_transmit(const uint8_t * data, uint8_t data_size);
void CAN_recive(uint16_t * address, uint8_t * data, uint8_t * data_size);
void CAN_test();


#endif /* CAN_CONTROLLER_H_ */