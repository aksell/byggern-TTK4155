#include "solenoide.h"

void init_solenoide(){
    DDRE |= (1 << PE4); // set pin as output
    PORTE &= ~(1 << PORTE4);  // set pin low
}

void trigger_solenoide(uint8_t solenoide_trigger_time){
    set_solenoide_position(1);
    _delay_ms(solenoide_trigger_time);
    set_solenoide_position(0);
}

void set_solenoide_position(uint8_t position){
    if !(position){
        PORTE &= ~(1 << PORTE);
    } else {
        PORTE |= (1 << PORTE4);
    }
}
