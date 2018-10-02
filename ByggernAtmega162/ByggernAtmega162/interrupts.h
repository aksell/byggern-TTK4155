/*
 * interrupts.h
 *
 * Created: 26.09.2018 13:39:18
 *  Author: EdvardOlaf
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "push_buttons.h"
#include <avr/interrupt.h>

//Sets up interrupts on INT0 and INT1
void interrupt_init();


#endif /* INTERRUPTS_H_ */