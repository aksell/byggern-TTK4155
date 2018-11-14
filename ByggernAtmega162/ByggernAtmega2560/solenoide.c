#include "solenoide.h"

#define SOLENOID_PRE_SCALAR 1024
#define SOLENOID_PRE_SCALAR_BM 0b101
#define SOLENOID_TRIGGER_PIN PH1
void solenoide_init(){
    DDRH |= (1 << SOLENOID_TRIGGER_PIN); // set pin as output
    PORTH &= ~(1 << SOLENOID_TRIGGER_PIN);  // set pin low
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		TCCR1A = (0b00 << COM1A0) | (0b00 << COM1B0) |  (0b00 << WGM10);	//Toggle OC1A on Compare Match, OC1B and OC1C disconnected
		//Set Wave gen to 15 (Fast PWM) and
		TCCR1B = (0b000 << CS10) | (0b01 << WGM12);
		TIMSK1 |= (1 << OCIE1A);
		OCR1A = F_CPU/SOLENOID_PRE_SCALAR-1;
	}
}

ISR(TIMER1_COMPA_vect) {
	solenoide_set_position(0); 
	TCCR1B &= ~(0b111 << CS10); //Stop timer
	TCNT1 = 0;
}

void solenoide_trigger(uint16_t solenoide_trigger_time_ms){
	solenoide_set_position(1);
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR1A = F_CPU*solenoide_trigger_time_ms*4/(SOLENOID_PRE_SCALAR*1000); //Set time interval
		TCNT1 = 0; 
		TCCR1B |= (SOLENOID_PRE_SCALAR_BM << CS10); //Start timer
	}
}

void solenoide_set_position(uint8_t position){
    if (position){
        PORTH &= ~(1 << SOLENOID_TRIGGER_PIN);
    } else {
        PORTH |= (1 << SOLENOID_TRIGGER_PIN);
    }
}
