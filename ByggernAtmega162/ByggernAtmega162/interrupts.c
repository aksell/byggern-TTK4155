/*
 * interrupts.c
 *
 * Created: 26.09.2018 13:39:03
 *  Author: EdvardOlaf
 */ 
#include "interrupts.h"

void interrupt_init() {
	
	DDRD &= ~(1<<PD2);		// Set port D pin 2
	cli();
	 
	
	
	GICR |= 1<<INT0;					// Enable INT0
	//GICR |= 1<<INT1;					// Enable INT1
	MCUCR |= 1<<ISC11 | 0<<ISC10;	// Trigger INT1 on rising edge
	//MCUCR |= 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge
	sei();
}

ISR(INT0_vect)
{
	can_message message;
	CAN_recive_message(&message);
	CAN_buffer_write(&message);
	MCP2515_bit_modify(MCP_CANINTF,(1<<0),0);
}


ISR(INT1_vect)
{
	
}
