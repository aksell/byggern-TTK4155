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
		DDRH |= (1 << PH3);
		TCCR4A = (0b01 << COM4A0) | (0b00 << COM4B0) |  (0b11 << WGM40);	//Toggle OC1A on Compare Match, OC1B and OC1C disconnected
		//Set Wave gen to 15 (Fast PWM) and
		TCCR4B = (0b000 << CS40) | (0b11 << WGM42);
		OCR4A = hz_to_timer_top(500);
	}
}



void speaker_set_hz(uint16_t hz) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR4A = hz_to_timer_top(hz);
		OCR4B = OCR2A/2;
	}
}

void speaker_off() {
	TCCR4B = TCCR4B & ~(0b111 << CS40);//Set prescalar to 0
}

void speaker_on() {
	TCCR4B = (TCCR4B & ~(0b111 << CS40)) | (PWM_PRESCALER_BITMAP << CS40); //Set prescalar to 1
}

uint16_t hz_to_timer_top(uint16_t hz) {
	return (F_CPU/PWM_PRESCALER)/(2*hz)-1;
}

