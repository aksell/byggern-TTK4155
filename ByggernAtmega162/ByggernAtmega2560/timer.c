/*
 * timer.c
 *
 * Created: 07.11.2018 18:19:20
 *  Author: torbjfug
 */ 

#include "timer.h"

#define TIMER0_PRESCALER 1024

void timer0_init(){

	TCCR0A |= (1<<WGM01); //Clear on compare match
	TCCR0B |= (1<<CS02)|(1<<CS00); //Prescaler 1024
	if (TIMER0_FREQUENZY < 31){
		OCR0A = 0xff;
	}
	else{
		OCR0A = F_CPU/2/TIMER0_FREQUENZY/TIMER0_PRESCALER - 1;
	}
	TIMSK0 |= (1<<OCIE0A);	//Enable itmer interrupt

}


ISR(TIMER0_COMPA_vect){
	dc_motor_PI_controller_update();
}