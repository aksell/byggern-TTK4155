/*
 * buttons.h
 *
 * Created: 26.09.2018 11:30:25
 *  Author: EdvardOlaf
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "utilities.h"

void buttons_init();

void buttons_set_state(int button_index, bool button_state);
bool buttons_get_state(int button_index);

#endif /* BUTTONS_H_ */