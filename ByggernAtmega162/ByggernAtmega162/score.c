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
	score_reset();
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
	//ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		score_increment();
	//}
}

void score_high_score_display_init() {
	oled_clear_screen();
	uint8_t high_score = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		high_score = EEPROM_read(EEPROM_HIGH_SCORE);
		if(high_score < score_count) {
			high_score = score_count;
			EEPROM_write(EEPROM_HIGH_SCORE, high_score);	
		}
	}
	
	stdout = &oled_stream;
	oled_columb_range_select(20, 120);
	oled_page_select(1);
	printf("Game score:");
	oled_columb_range_select(50, 120);
	oled_page_select(2);
	printf("%03i", score_count);
	
	oled_page_select(4);
	oled_columb_range_select(20, 120);
	printf("High score:");
	oled_page_select(5);
	oled_columb_range_select(50, 120);
	printf("%03i", high_score);
}

void score_reset_high_score(int dummy_int) {
	EEPROM_write(EEPROM_HIGH_SCORE, 0);
}
