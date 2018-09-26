/*
 * timer.c
 *
 * Created: 26.09.2018 15:43:43
 *  Author: torbjfug
 */ 

#include "timer.h"


void timer_init(){
	
	//TNCNT1 = F_CPU/10;
	
	TCCR1B = (1<<CS12 | 1 << CS10); //Pre scaler 1024

	OCR1A =  960;// Set timer length 200 ms(timer_length*F_CPU/(pre_scaler*timer_length)
	TCNT1 = 0;
}

bool timer_done(){
	return (TIFR & (1<<OCF1A));
}

void timer_reset(){
	TCNT1 = 0;
	TIFR |= (1<<OCF1A);
}
