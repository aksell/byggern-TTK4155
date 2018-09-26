/*
 * buttons.h
 *
 * Created: 26.09.2018 11:30:25
 *  Author: EdvardOlaf
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "utilities.h"

void push_buttons_init();

void push_buttons_set_state(int button_index, bool button_state);
bool push_buttons_get_state(int button_index);

#endif /* BUTTONS_H_ */