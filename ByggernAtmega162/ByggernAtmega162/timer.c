/*
 * timer.c
 *
 * Created: 26.09.2018 15:43:43
 *  Author: torbjfug
 */ 

#include "timer.h"


void timer1_init(){
	//TNCNT1 = F_CPU/10;
	TCCR1B = (1<<CS12 | 1 << CS10); //Pre scaler 1024
	OCR1A =  960;// Set timer length 200 ms (timer_length*F_CPU/pre_scaler
	TCNT1 = 0;
}

bool timer1_done(){
	return (TIFR & (1<<OCF1A));
}

void timer1_reset(){
	TCNT1 = 0;
	TIFR |= (1<<OCF1A);
}


void timer2_init(){
	TCCR3B = (1<<CS12 | 1 << CS10); //Pre scaler 1024
	OCR3A =  240;// Set timer frequency 60 Hz (timer_length*F_CPU/(pre_scaler*timer_length)
	TCNT3= 0;
}
void timer2_reset(){
	return (TIFR & (1<<OCF3A));
}
bool timer2_done(){
	TCNT3 = 0;
	TIFR |= (1<<OCF3A);
}