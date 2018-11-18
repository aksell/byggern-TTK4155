/*
 * spi.h
 *
 * Created: 03.10.2018 09:17:10
 *  Author: torbjfug
 */ 


#ifndef SPI_H_
#define SPI_H_

#define MAX_CAN_LENGTH 10

#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include "config.h"

//Initialize spi as master
void spi_init();

//As master sends an array send_data of uint8_t of length data_lenth and records received values on the array recived_data
void spi_transmit_recieve(uint8_t * send_data, uint8_t * recieve_data, uint8_t data_length);

//Reads as master data_length bytes of the SPI bus
void spi_receive(uint8_t * recieve_data, uint8_t data_length);


//Writes as master data_length bytes on the SPI bus
void spi_transmit(uint8_t * send_data,uint8_t data_length);

#endif /* SPI_H_ */