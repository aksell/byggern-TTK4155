/*
 * score.c
 *
 * Created: 10.11.2018 14:26:43
 *  Author: torbjfug
 */ 

#include "score.h"

uint8_t score_count; //real score value
uint8_t score_pre_scalar; //Scaling factor from 10 HZ from timer 2
uint8_t score_pre_count;

void score_init(){
	timer0_init();
	score_pre_scalar = 10;
}

void score_reset(){
	score_count = 0;
	score_pre_count = 0;
}

void score_start_counting(){
	timer0_enable();
}

void score_stop_counting(){
	timer0_dissable();
}

void score_set(uint8_t score){
	score_count = score;
}

void score_increment(){
	score_pre_count += 1;
	if (score_pre_count >= score_pre_scalar && score_count < 255){
		score_count += 1;
		score_pre_count = 0;
	}
}

uint8_t score_get(){
	return score_count;
}

ISR(TIMER0_COMP_vect){
	score_increment();
}