/*
 * dc_motor.c
 *
 * Created: 03.11.2018 17:13:05
 *  Author: torbjfug
 */ 
#include "dc_motor.h"

int16_t dc_motor_max_pos;
int16_t dc_motor_refference_pos;
uint8_t dc_motor_K_p;
uint8_t dc_motor_K_i;
int16_t dc_motor_accumulated_error;
uint16_t dc_motor_sample_time;
bool update_pid;


void dc_motor_encoder_reset_togle(){
	PORTH &=~(1<<PH6); //Reset encoder
	_delay_us(10);
	PORTH |=(1<<PH6);
}

void dc_motor_init(){
		DDRH |= (1<<PH1)|(1<<PH3)|(1<<PH4)|(1<<PH5)|(1<<PH6); //Set MJ1 as output
		PORTH |= (1<<PH1);//Direction right
		PORTH|=(1<<PH4);//Enable motor
		PORTH|= ~(1<<PH5); 
		/*PORTH &=~(1<<PH6); //Reset encoder
		_delay_us(10);
		PORTH |=(1<<PH6);*/
		dc_motor_encoder_reset_togle();
		dc_motor_K_i = 7;
		dc_motor_K_p = 15;
		
		dc_motor_accumulated_error = 0;
		dc_motor_sample_time = 1;
		dc_motor_calibrate_limits();
		dc_motor_refference_pos = dc_motor_max_pos/2;
		update_pid = 0;

}



void dc_motor_calibrate_limits(){
			dc_motor_set_speed(-100);
			_delay_ms(1500);
			dc_motor_set_speed(0);
			_delay_ms(500);
			dc_motor_encoder_reset_togle();
			dc_motor_set_speed(100);
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
		if(speed < -255){
			speed = -255;
		}
		dac_write(speed*(-1));
	}
	else{
		if(speed > 255){
			speed = 255;
		}
		dc_motor_set_dir(DC_MOTOR_LEFT);
		dac_write(speed);
	}	
}



int16_t dc_motor_encoder_read(){
	volatile int16_t encoder_val;
	volatile uint8_t low_val;
	volatile uint8_t high_val;
	PORTH &=~(1<<PH5); //Enable encoder output
	PORTH &= ~(1<<PH3); //Read select high bit
	_delay_us(20);
	high_val = (0xff)&(PINK);
	//encoder_val = encoder_val<<8;
	PORTH |= (1<<PH3);//Select low bit
	_delay_us(20);
	low_val = (0xff)&(PINK);
	PORTH |= (1<<PH5); //Disable encoder read
	encoder_val = convert_from_8_to_16(high_val,low_val);
	encoder_val = convert_from_2_compliment(encoder_val);
	return encoder_val;
}

void dc_motor_set_refference_possition(int16_t pos){
	dc_motor_refference_pos = dc_motor_max_pos/2 + dc_motor_max_pos*pos/100;
}




void dc_motor_PI_controller_update(){
	volatile int16_t current_position;
	current_position = dc_motor_encoder_read();
	int16_t error = (dc_motor_refference_pos - current_position)/256;
	dc_motor_accumulated_error += error;
	//printf("E_a:%i	",dc_motor_accumulated_error);
	//printf("E:%i	",error);
	int16_t u;
	u = (dc_motor_K_p*error) + 2*dc_motor_K_i*dc_motor_accumulated_error/PI_FREQUENZY;
	//printf("u:%d\n\r",u);
	dc_motor_set_speed(u);
}