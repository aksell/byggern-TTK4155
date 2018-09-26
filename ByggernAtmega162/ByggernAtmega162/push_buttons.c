/*
 * buttons.c
 *
 * Created: 26.09.2018 11:30:38
 *  Author: EdvardOlaf
 */ 

#include "push_buttons.h"

#define NUMB_BUTTONS 2

bool buttons_state[NUMB_BUTTONS];

void buttons_init() {
	for(int i = 0; i < NUMB_BUTTONS; i++) {
		buttons_state[i] = false;
	}
}

void buttons_set_state(int button_index, bool button_state) {
	buttons_state[button_index] = button_state;
}

bool buttons_get_state(int button_index) {
	int temp = buttons_state[button_index];
	buttons_state[button_index] = false;
	return temp;
}