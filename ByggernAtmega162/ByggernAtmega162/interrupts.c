/*
 * interrupts.c
 *
 * Created: 26.09.2018 13:39:03
 *  Author: EdvardOlaf
 */ 
#include "interrupts.h"

void interrupt0_init() {
	
	DDRD &= ~(1<<PD2);		// Set port D pin 2
	cli();
	GICR |= 1<<INT0;					// Enable INT0
	MCUCR |= 1<<ISC01; //| 1<<ISC00;	// Trigger INT0 on falling edge
	sei();
}

ISR(INT0_vect)
{	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		CAN_interrupt_routine();
	}	
}


ISR(USART0_RXC_vect)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		uint8_t data = uart_recive();
		uart_buffer_write(data);
	}
	//can_buffer_write(uart_recive());
}
