/*
 * timer.c
 *
 * Created: 24.10.2018 09:24:33
 *  Author: EdvardOlaf
 */ 

#include "timer.h"
#define PWM_PRESCALER 8
#define PWM_TOP F_CPU*2/(PWM_PRESCALER*100)

#define TIMER0_PRESCALER 1024


//Initalizes and starts a PWM signal on pin 5/PE3
void timer_init_fast_pwm_0() {

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		DDRE |= (1 << PE3);
		TCCR3A = (0b10 << COM3A0) |  (0b10 << WGM30) ;	//Toggle OC1A on Compare Match, OC1B and OC1C disconnected
														//Set Wave gen to 14 (Fast PWM) and 
		TCCR3B = (0b010 << CS30) | (0b11 << WGM32);		//Prescaler to 8
		ICR3 = PWM_TOP;
		OCR3A = PWM_TOP/20;
	}
}



//Sets the PWM output on pin 5/PE3
//Expects a value from 0 to 100
void timer_fast_pwm_duty_cycle(uint16_t per_cent_duty) {

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR3A = PWM_TOP/20+per_cent_duty*PWM_TOP/(20*1000);
	}
}



void timer0_init(){

	TCCR0A |= (1<<COM3A1)|(1<<WGM01); //Clear on compare match
	TCCR0B |= (1<<CS02)|(1<<CS00); //Prescaler 1024
	if (TIMER0_FREQUENZY < 31){
		OCR0A = 0xff;
	}
	else{
		OCR0A = F_CPU/2/TIMER0_FREQUENZY/TIMER0_PRESCALER - 1;
	}
	TIMSK0 |= (1<<OCIE0A);	

}


ISR(TIMER0_COMPA_vect){
	dc_motor_PI_controller_update();
}
