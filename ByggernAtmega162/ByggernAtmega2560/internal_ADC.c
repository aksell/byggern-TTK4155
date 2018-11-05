/*
 * internal_ADC.c
 *
 * Created: 31.10.2018 10:34:19
 *  Author: EdvardOlaf
 */ 

#include "internal_ADC.h"

//Initialize ADC on A0
void internal_ADC_init() {
	//Set MUXER
	ADMUX = (0b11 << REFS0) | (0b0000) | (1 << ADLAR);	//Select ADC0 and internal Referance and left adjust
	ADCSRB = (0b0 << MUX5);
	ADCSRA = (0b1 << ADEN) | (0b111 << ADPS0);			//Endable ADC and set prescalar to 64
	DIDR0 = 1;											//Disable digital buffer on ADC0
}

void internal_ADC_set_channel(uint8_t analog_channel) {
	if(channel < 8) {
		ADMUX = (ADMUX & 0B11100000) | channel;		// Set MUX4:0 to channel
		ADCSRB &= ~(1 << MUX5);						// Clear MUX5 bit
		DIDR0 = 1 << channel;						//Disable digital buffering
	} else {
		ADMUX = (ADMUX & 0B11100000) | channel-8;	// Set MUX4:0 to channel
		ADCSRB |= 1 << MUX5;						// Clear MUX5 bit
		DIDR2 = 1 << channel-8;						//Disable digital buffering
	}
}

//Reads analog value on A0
uint8_t internal_ADC_read() {
	ADCSRA |= (1 << ADSC);							//Start Conversion
	while(!(ADCSRA  & (1 << ADIF))) {};				//Whait for ADC to finish
	ADCSRA |= (1 << ADIF);							//Clear ADC ready flag
	return ADCH;
}
