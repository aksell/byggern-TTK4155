/*
 * spi.h
 *
 * Created: 03.10.2018 09:17:10
 *  Author: torbjfug
 */ 


#ifndef SPI_H_
#define SPI_H_

#define MAX_SPI_LENGTH 12

#include <avr/io.h>
#include "config.h"

//Initialize spi driver
void spi_init();

//Transmit and receive over spi
//Expects pointer to data to transmit, pointer to store recieved data in and length of tata to be transmittet
//Both send and recieve must be of equal length
void spi_transmit_recieve(uint8_t * send_data, uint8_t * recieve_data, uint8_t data_length);

//Receive data from spi. Expects length less than MAX_SPI_LENGTH  
void spi_receive(uint8_t * recieve_data, uint8_t data_length);

//Receive data from spi. Expects length less than MAX_SPI_LENGTH  
void spi_transmit(uint8_t * send_data,uint8_t data_length);

#endif /* SPI_H_ */