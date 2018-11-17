#ifndef SOLENOIDE_H_
#define SOLENOIDE_H_

#include "config.h"
#include <avr/io.h>
#include <util/atomic.h>


//Initialize the solenoid using PH0
void solenoide_init();

//Trigger the solenoid for solenoide_trigger_time_ms milli seconds
void solenoide_trigger(uint16_t solenoide_trigger_time_ms);

//Sets the solenoid position
void solenoide_set_position(uint8_t position);

#endif /* SOLENOIDE_H_ */
