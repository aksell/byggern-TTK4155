#ifndef SOLENOIDE_H_
#define SOLENOIDE_H_

#include "config.h"
#include <avr/io.h>
#include <util/atomic.h>

void solenoide_init();
void solenoide_trigger(uint16_t solenoide_trigger_time_ms);

void solenoide_set_position(uint8_t position);

#endif /* SOLENOIDE_H_ */
