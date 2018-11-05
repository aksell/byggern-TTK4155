/*
 * spi.h
 *
 * Created: 03.10.2018 09:17:10
 *  Author: torbjfug
 */ 


#ifndef SPI_H_
#define SPI_H_

#define MAX_CAN_LENGTH 12

#include <avr/io.h>
#include "config.h"

void spi_init();
void spi_transmit_recieve(uint8_t * send_data, uint8_t * recieve_data, uint8_t data_length);
void spi_receive(uint8_t * recieve_data, uint8_t data_length);
void spi_transmit(uint8_t * send_data,uint8_t data_length);

#endif /* SPI_H_ */