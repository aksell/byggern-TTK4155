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

//Initilize the pushbuttons connected to PD4 and PD5
void push_buttons_init();

//Returns true if the pushbutton has been pushed down since last call of push_buttons_get_state
bool push_buttons_get_state(push_button_t button);

//Read the value of the push button ports and  updates the states of the push button
void push_buttons_poll();

#endif /* BUTTONS_H_ */