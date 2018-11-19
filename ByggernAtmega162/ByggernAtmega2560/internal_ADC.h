/*
 * internal_ADC.h
 *
 * Created: 31.10.2018 10:34:39
 *  Author: EdvardOlaf
 */

#ifndef INTERNAL_ADC_H_
#define INTERNAL_ADC_H_
#include <avr/io.h>

// Initialize ADC on A0
void internal_ADC_init();

// Start free running mode on the ADC
void internal_ADC_start_free_running_mode();

// Stops free running mode on the ADC
void internal_ADC_stop_free_running_mode();

// Select analog channel to read from
void internal_ADC_set_channel(uint8_t analog_channel);

// Read form ADC when free running mode is disabled
uint8_t internal_ADC_read_polling();

// Read form ADC when free running mode is enable
uint8_t internal_ADC_read_free_running_mode();

#endif /* INTERNAL_ADC_H_ */