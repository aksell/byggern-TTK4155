/*
 * buttons.h
 *
 * Created: 26.09.2018 11:30:25
 *  Author: EdvardOlaf
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "utilities.h"


typedef enum push_button_e{
	PUSH_BUTTON_LEFT,
	PUSH_BUTTON_RIGHT
}push_button_t;

void push_buttons_init();

bool push_buttons_get_state(push_button_t button);

void push_buttons_poll();

#endif /* BUTTONS_H_ */