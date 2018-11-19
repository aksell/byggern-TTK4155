/*
 * timer.c
 *
 * Created: 10.11.2018 15:26:08
 *  Author: EdvardOlaf
 */ 

#include "timer.h"



uint16_t timer_counter;
uint16_t timer0_post_scaler;
uint16_t time;

void timer0_init(){

	TCCR0A = (1<<WGM01); //Clear on compare match
	TCCR0B = (1<<CS02)|(1<<CS00); //Prescaler 1024
	if (TIMER0_FREQUENZY < 62){
		OCR0A = 0xff;
	}
	else{
		OCR0A = F_CPU/TIMER0_PRESCALER/TIMER0_FREQUENZY - 1;
	}
	timer0_post_scaler = 0;
}

void timer0_enable(){
	TIMSK0 |= (1<<OCIE0A);
}

void timer0_dissable(){
	TIMSK0 &= ~(1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect){
	if(++timer0_post_scaler >= TIMER0_POST_SCALER_MAX){
		timer0_post_scaler = 0;
		dc_motor_PI_controller_update();
	}
}