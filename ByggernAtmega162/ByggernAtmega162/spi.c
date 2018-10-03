/*
 * spi.c
 *
 * Created: 03.10.2018 09:16:53
 *  Author: torbjfug
 */ 

#include "spi.h"

#define CAN_SPI_ID 0



void spi_init(){
	/* Set MOSI and SCK and CS output, all others input */
	DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);
	PORTB |= 1<<PB4;
	/* Enable interrupt */
	//SPSR = (1<<SPIF);
	//SPCR = 1<<SPIE;
	
	
	/* Enable SPI interrupt, SPI, Master, set clock rate fck/16 , SPI mode 0 by default*/
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	
}

void spi_transmit_recieve(uint8_t * send_data, uint8_t * recieve_data, uint8_t data_length){
	//Set chip select
	PORTB &= ~(1<<PB4);
	//SPSR &= ~(1<<SPIF);
	for (int i = 0;i<data_length;i++){
		SPDR = send_data[i];
		while(!(SPSR & (1<<SPIF)));
		recieve_data[i] = SPDR;
		
	}
	PORTB |= 1<<PB4;	
}

/*
void spi_receive(uint8_t * recieve_data, uint8_t data_length){
	uint8_t data = 0;
	return spi_transmit_recieve(&datauint8_t * recieve_data, uint8_t data_length);
}

void spi_transmit(uint8_t * send_data,uint8_t data_length){
	uint8_t dummy_recieve [data_length];
	spi_transmit_recieve(send_data,dummy_recieve,uint8_t data_length);
}
*/

/*
		stdout = &uart_stream;
		uint8_t data [3];
		data[0]=1;
		data[1]=2;
		data[2]=3;
		
		uint8_t read_data [3];
		spi_transmit_recieve(data,read_data,3);
		for (int i = 0;i<3;i++){
			printf("Sending: %d\r\n",data[i]);
			
			printf("Recieving: %d\r\n", read_data[i]);
		}
		printf("\n");
		*/