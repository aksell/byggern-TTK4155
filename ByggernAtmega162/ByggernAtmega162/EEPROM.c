/*
 * EEPROM.c
 *
 * Created: 17.11.2018 11:43:42
 *  Author: torbjfug
 */

#include "EEPROM.h"

void EEPROM_write(EEPROM_address address, uint8_t data) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    while (EECR & (1 << EEWE)) {
    }; // Wait until  EEPROM Write Enable becomes zero.
    EEAR = address;
    EEDR = data;
    EECR = (EECR & ~(1 << EEWE)) | (1 << EEMWE); // Write a logical one to the
                                                 // EEMWE bit while writing a
                                                 // zero to EEWE in EECR.
    EECR |= (1 << EEWE); // Within four clock cycles after setting EEMWE, write
                         // a logical one to EEWE.
  }
}

uint8_t EEPROM_read(EEPROM_address address) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    while (EECR & (1 << EEWE))
      ; // Wait for completion of previous write
    EEAR = address;
    EECR |= (1 << EERE); // Start eeprom read by writing EERE
    return EEDR;         // Return data from data register
  }
}
