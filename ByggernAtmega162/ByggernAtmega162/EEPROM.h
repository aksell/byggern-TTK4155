/*
 * EEPROM.h
 *
 * Created: 17.11.2018 11:43:29
 *  Author: torbjfug
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <util/atomic.h>
#include <avr/io.h>


typedef enum EEPROM_address_e{
	EEPROM_HIGH_SCORE
}EEPROM_address;

//Write to the EEPROM
void EEPROM_write(EEPROM_address address, uint8_t data);

//Read to the EEPROM
uint8_t EEPROM_read(EEPROM_address address);

#endif /* EEPROM_H_ */