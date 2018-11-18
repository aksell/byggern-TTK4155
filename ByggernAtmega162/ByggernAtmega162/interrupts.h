/*
 * interrupts.h
 *
 * Created: 26.09.2018 13:39:18
 *  Author: EdvardOlaf
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


#include <avr/interrupt.h>
#include <util/atomic.h>
#include "CAN_controller.h"
#include "CAN_buffer.h"
#include "push_buttons.h"
#include "MCP2515_driver.h"
#include "MCP2515_reg.h"
#include "uart.h"
#include "uart_buffer.h"

//Sets up interrupts on INT0 for CAN_interrupt_routine
void interrupt0_init();


#endif /* INTERRUPTS_H_ */