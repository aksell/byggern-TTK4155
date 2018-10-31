/*
 * dac.c
 *
 * Created: 31.10.2018 10:38:03
 *  Author: torbjfug
 */ 

#include "dac.h"

typedef struct twi_message_s{
	uint8_t data_size;
	bool read_write;
	uint8_t slave_addres;
	uint8_t* data
}twi_message;

void dac_init(){
	TWI_Master_Initialise();
}

void dac_write(uint8_t data){	
	uint8_t message[TWI_BUFFER_SIZE];
	message[0] = DAC_SLAVE_ADDRES<<1;
	message[0] &= ~(0b1); //Write operation
	message[0] = 0b01010000;
	message[1] = 0;
	message[2] = data;
	TWI_Start_Transceiver_With_Data(&message[0],TWI_BUFFER_SIZE);
}