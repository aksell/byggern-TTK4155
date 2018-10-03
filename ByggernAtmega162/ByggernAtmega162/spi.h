/*
 * spi.h
 *
 * Created: 03.10.2018 09:17:10
 *  Author: torbjfug
 */ 


#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>
#include "config.h"

void spi_init();
void spi_transmit_recieve(uint8_t * send_data, uint8_t * recieve_data, uint8_t data_length);
uint8_t spi_receive();
void spi_transmit(uint8_t * data);

#endif /* SPI_H_ */