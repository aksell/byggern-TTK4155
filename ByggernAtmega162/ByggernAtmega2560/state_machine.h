/*
 * state_machine.h
 *
 * Created: 07.11.2018 18:29:33
 *  Author: EdvardOlaf
 */ 


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "../ByggernAtmega162/CAN_protocol.h"
#include "CAN_buffer.h"
#include "CAN_controller.h"
#include "servo.h"
#include "music.h"
#include "dc_motor.h"
#include "ball_sensor.h"
#include "uart.h"

void state_machine_init();
void state_machine_update();

#endif /* STATE_MACHINE_H_ */