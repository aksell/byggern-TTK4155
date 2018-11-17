/*
 * ball_sensor.h
 *
 * Created: 07.11.2018 18:10:09
 *  Author: EdvardOlaf
 */ 


#ifndef BALL_SENSOR_H_
#define BALL_SENSOR_H_

#include <avr/io.h>
#include "internal_ADC.h"
#include "utilities.h"

//Initialize IR ball sensor on analog input 0
void ball_sensor_init();

//Returns true if ball sensor is triggered
bool ball_sensor_is_triggered();


#endif /* BALL_SENSOR_H_ */