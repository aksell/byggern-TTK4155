/*
 * timer.c
 *
 * Created: 24.10.2018 09:24:33
 *  Author: EdvardOlaf
 */ 

#include "servo.h"
#define PWM_PRESCALER 8
#define PWM_TOP F_CPU*2/(PWM_PRESCALER*100)


//Initalizes and starts a PWM signal on pin 5/PE3
void servo_init_fast_pwm_3() {

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
//Expects a value from 0 to 255
void servo_fast_pwm_duty_cycle(int8_t duty) {
	int16_t duty_cycle = duty;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR3A = PWM_TOP/20+(duty_cycle+128)*PWM_TOP/(20*255);
	}
}



