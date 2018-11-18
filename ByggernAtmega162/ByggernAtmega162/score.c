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
bool score_screen_outdated;

void score_init(){
	timer0_init();
	score_pre_scalar = 10;
	score_screen_outdated = false;
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
		score_screen_outdated = true;
		score_pre_count = 0;
	}
}

uint8_t score_get(){
	return score_count;
}

bool score_is_screen_outdated() {
	return score_screen_outdated;	
}

void score_screen_init() {
	oled_clear_screen();
	stdout = &oled_big_stream;
	oled_print_char_big_set_start(20, 3);
	printf("%03i",	score_get());
	stdout = &oled_stream;
	oled_set_printf_page(1);
	oled_columb_range_select(40, 100);
	printf("Score:");
	oled_set_printf_page(7);
	oled_columb_range_select(0, 100);
	printf("Abort");
}

void score_screen_update() {
	stdout = &oled_big_stream;
	oled_print_char_big_set_start(20, 3);
	printf("%03i",	score_get());
	stdout = &oled_stream;
	score_screen_outdated = false;
}

ISR(TIMER0_COMP_vect){
	score_increment();
}