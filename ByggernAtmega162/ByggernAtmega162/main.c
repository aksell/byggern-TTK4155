/*
 * ByggernAtmega162.c
 *
 * Created: 29.08.2018 13:48:18
 * Author : EdvardOlaf
 */ 
 #define F_CPU 4.915E6

#include <avr/io.h>
#include <util/delay.h>
#include<stdlib.h>

int main(void)
{
	DDRA |= 0b1;
	PORTA |= 0b1;
    /* Replace with your application code */
    while (1) 
    {
		PORTA |= 0b1;
		_delay_ms(1000);
		PORTA &= ~0b1;
		_delay_ms(1000);
    }
}

