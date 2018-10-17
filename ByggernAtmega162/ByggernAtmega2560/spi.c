/*
 * spi.c
 *
 * Created: 03.10.2018 09:16:53
 *  Author: torbjfug
 */ 

#include "spi.h"

#define SS_PIN PB7
#define SCK_PIN PB1
#define MOSI_PIN PB2
#define MISO_PIN PB3

void spi_init(){

	/* Set MOSI and SCK and CS output, all others input */
	DDRB = (1<<MOSI_PIN)|(1<<SCK_PIN)|(1<<SS_PIN)|(1 << PB0);
	PORTB |= (1<<SS_PIN) | (1 << PB0);
	/* Enable interrupt */
	//SPSR = (1<<SPIF);
	//SPCR = 1<<SPIE;	
	/* Enable SPI interrupt, SPI, Master, set clock rate fck/16 , SPI mode 0 by default*/
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	
}

void spi_transmit_recieve(uint8_t * send_data, uint8_t * recieve_data, uint8_t data_length){
	//Set chip select
	PORTB &= ~(1<<SS_PIN);

	for (uint8_t i = 0;i<data_length;i++){
		SPDR = send_data[i]; //Send data
		while(!(SPSR & (1<<SPIF))); //Wait for transmission to complete
		recieve_data[i] = SPDR; //Read incoming data
	}
	PORTB |= 1<<SS_PIN;	
}


void spi_receive(uint8_t * recieve_data, uint8_t data_length){
	uint8_t dummy_data[MAX_CAN_LENGTH];
	spi_transmit_recieve(dummy_data, recieve_data, data_length);
}

void spi_transmit(uint8_t * send_data,uint8_t data_length){
	uint8_t dummy_recieve [MAX_CAN_LENGTH];
	spi_transmit_recieve(send_data, dummy_recieve, data_length);
}
