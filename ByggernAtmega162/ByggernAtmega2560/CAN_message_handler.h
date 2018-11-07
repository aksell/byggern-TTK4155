/*
 * CAN_message_handler.h
 *
 * Created: 24.10.2018 15:44:40
 *  Author: torbjfug
 */ 


#ifndef CAN_MESSAGE_HANDLER_H_
#define CAN_MESSAGE_HANDLER_H_
#include "config.h"
#include "utilities.h"
#include "../ByggernAtmega162/CAN_protocol.h"
#include "CAN_buffer.h"
#include "CAN_controller.h"
#include "uart.h"
#include "dac.h"
#include "dc_motor.h"
#include <stdint.h>

void CAN_message_handler();

//Transmit joystick value
void CAN_IR_transmit();


#endif /* CAN_MESSAGE_HANDLER_H_ */