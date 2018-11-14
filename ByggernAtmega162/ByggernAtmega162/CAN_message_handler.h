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
#include "CAN_protocol.h"
#include "CAN_buffer.h"
#include "CAN_controller.h"
#include "uart.h"
#include "joystick.h"
#include "slider.h"
#include "ping_pong_loop.h"
#include "push_buttons.h"

void CAN_message_handler();

//Transmit joystick value
void CAN_joystick_X_transmit();
void CAN_joystick_Y_transmit();

//Transmits current slider value
void CAN_slider_transmit();


//Transmits current button state
void CAN_push_button_transmit();


#endif /* CAN_MESSAGE_HANDLER_H_ */