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
	ADCSRA = (0b1 << ADEN) | (0b110 << ADPS0);			//Endable ADC and set prescalar to 64
	DIDR0 = 1;											//Disable digital buffer on ADC0
}


//Reads analog value on selected channel
uint8_t internal_ADC_read_polling() {
	ADCSRA |= (1 << ADSC);							//Start Conversion
	while(!(ADCSRA  & (1 << ADIF))) {};				//Wait for ADC to finish
	ADCSRA |= (1 << ADIF);							//Clear ADC ready flag
	return ADCH;
}

void internal_ADC_start_free_running_mode() {
	ADCSRA |= (1 << ADATE);			//ADC Auto Trigger ENABLE
	ADCSRB &= ~(0b111 << ADTS0);	//ADC Auto Trigger Source ro running mode
	ADCSRA |= (1<< ADSC); 

}

void internal_ADC_stop_free_running_mode() {
	ADCSRA &= ~(1 << ADATE);		//ADC Auto Trigger Disable
	ADCSRB &= ~(0b111 << ADTS0);	//ADC Auto Trigger Source to running mode
}

//Select analog channel to read from.
void internal_ADC_set_channel(uint8_t analog_channel) {
	uint8_t enable_free_running_mode = 0;
	if(ADCSRA & (1 << ADATE)) {
		enable_free_running_mode = 1;
		internal_ADC_stop_free_running_mode();
	}
	if(analog_channel < 8) {
		ADMUX = (ADMUX & 0B11100000) | analog_channel;		// Set MUX4:0 to channel
		ADCSRB &= ~(1 << MUX5);						// Clear MUX5 bit
		DIDR0 = 1 << analog_channel;						//Disable digital buffering
	} else {
		ADMUX = (ADMUX & 0B11100000) | analog_channel-8;	// Set MUX4:0 to channel
		ADCSRB |= 1 << MUX5;						// Clear MUX5 bit
		DIDR2 = 1 << analog_channel-8;						//Disable digital buffering
	}
	if(enable_free_running_mode) {
		internal_ADC_start_free_running_mode();
	}
}
uint8_t internal_ADC_read_free_running_mode() {
	return ADCH;
}
