/*
 * state_machine.h
 *
 * Created: 07.11.2018 18:29:42
 *  Author: torbjfug
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "CAN_buffer.h"
#include "CAN_controller.h"
#include "CAN_protocol.h"
#include "EEPROM.h"
#include "config.h"
#include "joystick.h"
#include "oled_menu.h"
#include "push_buttons.h"
#include "score.h"
#include "slider.h"
#include "timer.h"
#include "uart.h"
typedef enum states_e { MENU, IDLE, IN_GAME, GAME_OVER, DISPLAY_STATS } state_t;

// Initialize the state machine
void state_machine_init();

// Updates the state machine
void state_machine_update();

// Sets the next state of the state machine
void state_machine_set_next_state(state_t next_state);

// Start a song on the state machine
void state_machine_set_game_music(uint8_t song);

// Function to let the oled menu start a game
void state_machine_set_in_game(int dummy_int);

// Forces node 2 to calibrate motor
void state_machine_calibrate_motor(int dummy_int);

#endif /* STATE_MACHINE_H_ */