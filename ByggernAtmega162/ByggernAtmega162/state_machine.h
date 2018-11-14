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
#include "CAN_buffer.h"
#include "CAN_controller.h"
#include "CAN_protocol.h"
#include "oled_menu.h"
#include "uart.h"
#include "score.h"

typedef enum states_e {
	MENU,
	IDLE,
	IN_GAME,
	DISPLAY_STATS
}state_t;

void state_machine_init();
void state_machine_update();
void state_machine_set_next_state(state_t next_state);
void state_machine_start_game(int dummy_int);
void state_machine_set_game_music(uint8_t song);
void state_machine_set_in_game(int dummy_int);





#endif /* STATE_MACHINE_H_ */