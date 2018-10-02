/*
 * OLED.c
 *
 * Created: 19.09.2018 10:07:50
 *  Author: torbjfug
 */ 


#include "oled.h"


void oled_data_write(uint8_t data);
void oled_control_write(uint8_t data);

void oled_init()
{
	oled_control_write(0xae); //display off
	oled_control_write(0xa1); //segment remap
	oled_control_write(0xda); //common pads hardware: alternative ????
	oled_control_write(0x12);
	oled_control_write(0xc8); //common output scan direction:com63~com0
	oled_control_write(0xa8); //multiplex ration mode:63
	oled_control_write(0x3f);
	oled_control_write(0xd5); //display divide ratio/osc. freq. mode
	oled_control_write(0x80);
	oled_control_write(0x81); //contrast control
	oled_control_write(0x50);
	oled_control_write(0xd9); //set pre-charge period
	oled_control_write(0x21);
	oled_control_write(0x20); //Set Memory Addressing Mode PAGE MODE
	oled_control_write(0x02);
	oled_control_write(0xdb); //VCOM deselect level mode
	oled_control_write(0x30);
	oled_control_write(0xad); //master configuration
	oled_control_write(0x00);
	oled_control_write(0xa4); //out follows RAM content
	oled_control_write(0xa6); //set normal display
	oled_control_write(0xaf); // display on
	
	oled_clear_screen();
}

void oled_columb_range_select(uint8_t start, uint8_t end){
	oled_control_write(OLED_COLUMB_SET);
	if (start < OLED_COLUMBS){
		oled_control_write(start);
	}
	else{
		oled_control_write(OLED_COLUMBS-1);
	}
	
	if (end < OLED_COLUMBS){
		oled_control_write(end);
	}
	else{
		oled_control_write(OLED_COLUMBS-1);
	}
}

void oled_page_select(uint8_t page){
	oled_control_write(OLED_PAGE_SET);
	if (page < OLED_PAGES){
		oled_control_write(page);
		oled_control_write(page);
	}
	else{
		oled_control_write(OLED_PAGES-1);
		oled_control_write(OLED_PAGES-1);
	}
}

void oled_clear_page(uint8_t page){
	if (page < OLED_PAGES){
		oled_page_select(page);
		oled_columb_range_select(0,OLED_COLUMBS-1);		
		for (int i = 0;i<OLED_COLUMBS;i++){
			oled_data_write(0x00);
		}
	}
}

void oled_chess() {
	for (int i = 0; i < 128/8;i++){
		for(int j = 0; j < 6; j++) {
			oled_set_value_range(j,i*16+(j%2)*8,i*16+8+(j%2)*8,0xd0);
		}
	}
}

void oled_clear_screen(){
	for (int i = 0;i<OLED_PAGES;i++){
		oled_clear_page(i);
	}
}

void oled_set_value_range(uint8_t page,  uint8_t start, uint8_t end,uint8_t val){
	oled_columb_range_select(start,end);
	oled_page_select(page);
	for (int i = start; i <= end;i++){
		oled_data_write(val);
	}
}


void oled_white_screen(){
	for (int page = 0; page<OLED_PAGES;page++){
		oled_set_value_range(page,0,OLED_COLUMBS-1,0xff);
	}
	
}

void oled_data_write(uint8_t data){
	volatile uint8_t *adress = OLED_DATA_OFFSET;
	*adress = data;
}

void oled_control_write(uint8_t data){
	volatile uint8_t *adress = OLED_CMD_OFFSET;
	*adress = data;	
}

bool printf_inverted = false;

void oled_printf_inverted() {
	printf_inverted = true;
}

void oled_printf_normal() {
	printf_inverted = false;
}


uint8_t printf_columb = 0;
uint8_t printf_page = 0;
uint8_t printf_size = 0;

void oled_set_printf_page(uint8_t page) {
	printf_page = page;
	oled_page_select(printf_page);
}

void oled_set_printf_size(uint8_t size) {
	printf_size = size;
}

uint8_t oled_print_char(char letter) {
	if(letter == '\n') {
		printf_page+=1;
		oled_page_select(printf_page);
		oled_columb_range_select(0, OLED_COLUMBS);
	} else {
		oled_print_char_of_size(letter, printf_size);
		uint8_t columb_adder = 0;
	}
	return 0;
}

uint8_t oled_printf_dummy_recieve(){
	return 0;
	
}


void oled_print_char_of_size(char letter,  uint8_t size) {
	uint8_t char_length = 0;
	unsigned char ** letter_bitmap;
	if(size == FONT_SIZE_SMALL) {
		char_length = 4;
		letter_bitmap = font4;
	} else if(size == FONT_SIZE_MEDIUM) {
		char_length = 5;
		letter_bitmap = font5;
	} else{
		char_length = 8;
		letter_bitmap = font8;
	}
	for(int i = 0; i < 8; i++) {
		if(!printf_inverted) {
			oled_data_write(pgm_read_byte(&(font8[letter - ' '][i])));
		} else {
			oled_data_write(~pgm_read_byte(&(font8[letter - ' '][i])));
		}
	}
}