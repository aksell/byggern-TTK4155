/*
 * timer.c
 *
 * Created: 24.10.2018 09:24:33
 *  Author: EdvardOlaf
 */ 

#include "timer.h"
#define PWM_PRESCALER 8
#define PWM_TOP F_CPU*2/(PWM_PRESCALER*100)
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

void timer_test() {
	printf("%i\n\r", TCNT3);
}

void timer_fast_pwm_duty_cycle(uint16_t per_cent_duty) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR3A = PWM_TOP/20+per_cent_duty*PWM_TOP/(20*1000);
	}
}

