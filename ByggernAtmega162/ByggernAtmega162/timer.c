/*
 * timer.c
 *
 * Created: 26.09.2018 15:43:43
 *  Author: torbjfug
 */ 

#include "timer.h"
#define PRE_SCALAR_1_3 1024
#define PRE_SCALAR_0 1024
#define TIMER0_FREQ 10
#define TIMER1_FREQ 5
#define TIMER3_FREQ 10

void timer0_init(){
	TCCR0 |= (1<<WGM01); //Clare on compare match
	TCCR0 |= (1<<CS12)|(1 << CS10);  //Pre scaler 1024
	if(TIMER0_FREQ > 10){
		OCR0 =  F_CPU/PRE_SCALAR_0/TIMER0_FREQ/2 - 1;
	}
	else{
		OCR0 = 0xff;
	}
}

void timer0_enable(){
	TIMSK |= (1<<TOIE0); //Enable timer interrupt
}
void timer0_dissable(){
	TIMSK &= ~(1<<TOIE0); //Dissable timer interrupt
}


void timer1_init(){
	//TNCNT1 = F_CPU/10;
	TCCR1B = (1<<CS12) | (1 << CS10); //Pre scaler 1024
	OCR1A = F_CPU/PRE_SCALAR_1_3/TIMER1_FREQ;// Set timer length
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


void timer3_init(){
	TCCR3A |= (1<<COM3A1); //Clear on compare match
	TCCR3B = (1<<CS12)|(1 << CS10); //Pre scaler 1024
	OCR3A = F_CPU/PRE_SCALAR_1_3/TIMER3_FREQ; //Set timer frequency
	TCNT3= 0;
}
bool timer3_done(){
	return (TIFR & (1<<OCF3A));
}
void timer3_reset(){
	TCNT3 = 0; //Set counter to zero
	TIFR |= (1<<OCF3A); //Reset 
}

