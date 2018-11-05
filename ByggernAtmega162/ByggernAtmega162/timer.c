/*
 * timer.c
 *
 * Created: 26.09.2018 15:43:43
 *  Author: torbjfug
 */ 

#include "timer.h"
#define PRE_SCALAR_1_3 1024
#define TIMER3_FREQ 1
#define TIMER1_FREQ 3


void timer1_init(){
	//TNCNT1 = F_CPU/10;
	TCCR1B = (1<<CS12 | 1 << CS10); //Pre scaler 1024
	OCR1A = F_CPU/PRE_SCALAR_1_3/TIMER1_FREQ;// Set timer length 200 ms (timer_length*F_CPU/pre_scaler
	//OCR1A =  960;
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
	OCR3A = F_CPU/PRE_SCALAR_1_3/TIMER3_FREQ; //Set timer frequenzy
	//OCR3A =  240;// Set timer frequency 60 Hz (timer_length*F_CPU/(pre_scaler*timer_length)
	TCNT3= 0;
}
bool timer2_done(){
	return (TIFR & (1<<OCF3A));
}
void timer2_reset(){
	TCNT3 = 0;
	TIFR |= (1<<OCF3A);
}