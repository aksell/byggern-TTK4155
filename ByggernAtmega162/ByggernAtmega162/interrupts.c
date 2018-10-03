/*
 * interrupts.c
 *
 * Created: 26.09.2018 13:39:03
 *  Author: EdvardOlaf
 */ 
#include "interrupts.h"

void interrupt_init() {
	
	//DDRD &= ~(1<<PD2 |  1 << PD3);		// Set port D pin 2 and 3 to input
	cli();
	 
	//GICR |= 1<<INT0;					// Enable INT0
	//GICR |= 1<<INT1;					// Enable INT1
	MCUCR |= 1<<ISC11 | 1<<ISC10;	// Trigger INT1 on rising edge
	MCUCR |= 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge
	//sei();
}

ISR(INT0_vect)
{
	
}


ISR(INT1_vect)
{
	
}
