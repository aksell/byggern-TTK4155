#ifndef SOLENOIDE_H_
#define SOLENOIDE_H_

#include <avr/io.h>
#include <util/delay.h

void init_solenoide();
void trigger_solenoide(uint8_t solenoide_trigger_time);

void set_solenoide_position(uint8_t position);

#endif /* SOLENOIDE_H_ */
