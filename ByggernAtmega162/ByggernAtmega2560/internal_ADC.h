/*
 * internal_ADC.h
 *
 * Created: 31.10.2018 10:34:39
 *  Author: EdvardOlaf
 */ 


#ifndef INTERNAL_ADC_H_
#define INTERNAL_ADC_H_
#include <avr/io.h>

//Initialize ADC on A0
void internal_ADC_init();

//Reads analog value on A0
uint8_t internal_ADC_read(); 

#endif /* INTERNAL_ADC_H_ */