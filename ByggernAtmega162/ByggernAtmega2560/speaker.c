/*
 * speaker.c
 *
 * Created: 05.11.2018 11:47:23
 *  Author: EdvardOlaf
 */

#include "speaker.h"

#define PWM_PRESCALER 8UL
#define PWM_PRESCALER_BITMAP 0b010

void speaker_init() {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		DDRL |= (1 << PL3);
		TCCR5A = (0b01 << COM5A0) | (0b00 << COM5B0) |  (0b11 << WGM50);	//Toggle OC1A on Compare Match, OC1B and OC1C disconnected
		//Set Wave gen to 15 (Fast PWM) and
		TCCR5B = (0b000 << CS50) | (0b11 << WGM52);
		OCR5A = hz_to_timer_top(500);
	}
}



void speaker_set_hz(uint16_t hz) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR5A = hz_to_timer_top(hz);
		OCR5B = OCR2A/2;
	}
}

void speaker_off() {
	TCCR5B = TCCR5B & ~(0b111 << CS50);//Set prescalar to 0
}

void speaker_on() {
	TCCR5B = (TCCR5B & ~(0b111 << CS50)) | (PWM_PRESCALER_BITMAP << CS50); //Set prescalar to 1
}

uint16_t hz_to_timer_top(uint16_t hz) {
	return (F_CPU/PWM_PRESCALER)/(2*hz)-1;
}

