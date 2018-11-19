/*
 * dc_motor.c
 *
 * Created: 03.11.2018 17:13:05
 *  Author: torbjfug
 */ 
#include "dc_motor.h"

int16_t dc_motor_max_pos;
int16_t dc_motor_refference_pos;
int16_t dc_motor_middle_pos;
int16_t dc_motor_last_encoder_read;

uint8_t dc_motor_K_p;
uint8_t dc_motor_K_i;
int16_t dc_motor_accumulated_error;



#define DC_MOTOR_HYSTERESIS_UPPER 34
#define DC_MOTOR_HYSTERESIS_LOWER 0
#define DC_MOTOR_MAX_ERROR 2000

#define TIMER0_PRESCALER 1024


void dc_motor_init(){
	DDRH |= (1<<PH1)|(1<<PH3)|(1<<PH4)|(1<<PH5)|(1<<PH6); //Set MJ1 as output
	PORTH |= (1<<PH1);	//Direction right on dc_motor
	PORTH|=(1<<PH4);	//Enable motor
	dc_motor_encoder_reset_togle();
	
	//Set parameters for the motor controller
	dc_motor_K_i = 1;
	dc_motor_K_p = 5;
	dc_motor_accumulated_error = 0;

	dc_motor_calibrate_limits();
	dc_motor_middle_pos = dc_motor_max_pos/2;
	dc_motor_refference_pos = dc_motor_middle_pos;
	timer0_init();
}

void dc_motor_controller_enable(){
	timer0_enable();
}

void dc_motor_controller_dissable(){
	timer0_dissable();
}


void dc_motor_update_encoder() {
	dc_motor_last_encoder_read = dc_motor_encoder_read();
}

void dc_motor_encoder_reset_togle(){
	PORTH &=~(1<<PH6); //Reset encoder
	_delay_us(10);
	PORTH |=(1<<PH6); 
}





void dc_motor_calibrate_limits(){
			dc_motor_set_speed(-100+DC_MOTOR_HYSTERESIS_UPPER);
			_delay_ms(1500);
			dc_motor_set_speed(0);
			_delay_ms(500);
			dc_motor_encoder_reset_togle();
			dc_motor_set_speed(100-DC_MOTOR_HYSTERESIS_UPPER);
			_delay_ms(1500);
			dc_motor_set_speed(0);
			_delay_ms(500);
			dc_motor_max_pos = dc_motor_encoder_read();
}
void dc_motor_set_dir(dc_motor_dir dir){
	if (dir == DC_MOTOR_LEFT){
		PORTH &= ~(1<<PH1);
	}
	else if(dir == DC_MOTOR_RIGHT){
		PORTH |= (1<<PH1);
	}
}
void dc_motor_set_speed(int16_t speed){
	
	if(speed < 0){
		dc_motor_set_dir(DC_MOTOR_RIGHT);
		speed *= -1;
	}
	else{	
		dc_motor_set_dir(DC_MOTOR_LEFT);
	}
	if(speed > (255-DC_MOTOR_HYSTERESIS_UPPER)){
		speed = 255-DC_MOTOR_HYSTERESIS_UPPER;
	}
	if (speed > DC_MOTOR_HYSTERESIS_LOWER){ 
		dac_write(speed+DC_MOTOR_HYSTERESIS_UPPER);
	}
	else{
		dac_write(0);
	}

}



int16_t dc_motor_encoder_read(){
	volatile int16_t encoder_val;
	volatile uint8_t low_val;
	volatile uint8_t high_val;
	PORTH &=~(1<<PH5); //Enable encoder output
	PORTH &= ~(1<<PH3); //Read select high bit
	_delay_us(20);//Wait for lines to stabilize
	high_val = (0xff)&(PINK);
	PORTH |= (1<<PH3);//Select low bit
	_delay_us(20); //Wait for lines to stabilize
	low_val = (0xff)&(PINK);
	PORTH |= (1<<PH5); //Disable encoder read
	encoder_val = convert_from_8_to_16(high_val,low_val);
	encoder_val = convert_from_2_compliment(encoder_val);
	return encoder_val;
}


void dc_motor_set_refference_ofset(int16_t pos){
	//ensure value is valid
	if (pos> 255){
		pos = 255;
	}
	else if(pos < -255){
		pos = -255;
	}
	
	
	int32_t offset = pos*(dc_motor_max_pos/256)/2; //scale input fraction of working area
	dc_motor_refference_pos = dc_motor_middle_pos + (int16_t)offset;
}

void dc_motor_set_refference_middle(){
	dc_motor_set_refference_ofset(0);
}

void dc_motor_accumulate_error(int16_t eror){
	dc_motor_accumulated_error += eror;
	
	//Prevent overflow and too large integral effect if motor is stuck
	if (dc_motor_accumulated_error > DC_MOTOR_MAX_ERROR){ 
		dc_motor_accumulated_error = DC_MOTOR_MAX_ERROR;
	}
	else if (dc_motor_accumulated_error < -DC_MOTOR_MAX_ERROR){
		dc_motor_accumulated_error = -DC_MOTOR_MAX_ERROR;
	}
}



void dc_motor_PI_controller_update() {
 	dc_motor_update_encoder();		//Read encoder value
 	int16_t error = (dc_motor_refference_pos - dc_motor_last_encoder_read)/256;
 	dc_motor_accumulate_error(error);
	int16_t u = (dc_motor_K_p*error) + 2*dc_motor_K_i*dc_motor_accumulated_error/PI_FREQUENZY;
	dc_motor_set_speed(u);
}