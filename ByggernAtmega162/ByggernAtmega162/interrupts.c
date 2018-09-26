/*
 * interrupts.c
 *
 * Created: 26.09.2018 13:39:03
 *  Author: EdvardOlaf
 */ 
#include "interrupts.h"

void interrupt_init() {
	GICR = 1<<INT0;					// Enable INT0
	GICR = 1<<INT1;					// Enable INT1
	MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge
	
}

ISR(INT0_vect)
{
	buttons_set_state(0, 1);
}

ISR(INT1_vect)
{
	buttons_set_state(0, 1);
}