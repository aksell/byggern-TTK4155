/*
 * state_machine.h
 *
 * Created: 07.11.2018 18:29:42
 *  Author: torbjfug
 */ 


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "config.h"
#include "timer.h"
#include "slider.h"
#include "joystick.h"
#include "push_buttons.h"
#include "CAN_controller.h"
#include "oled_menu.h"
#include "uart.h"

void state_machine_init();
void state_machine_update();




#endif /* STATE_MACHINE_H_ */