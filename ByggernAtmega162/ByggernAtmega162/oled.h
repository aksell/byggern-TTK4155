/*
 * OLED.h
 *
 * Created: 19.09.2018 10:08:07
 *  Author: torbjfug
 */ 


#ifndef OLED_H_
#define OLED_H_

#include "config.h"
#include "external_mem.h"
#include "joystick.h"
#include <avr/pgmspace.h>
#include <stdio.h>

//#include "fonts.h"
#include "timer.h"


#include <util/delay.h>


#define OLED_PAGES 8
#define OLED_COLUMBS 128

#define OLED_COLUMB_SET 0x21
#define OLED_PAGE_SET 0x22


void oled_init();
//Select columb to start writing from
void oled_columb_range_select(uint8_t start, uint8_t end);
//Select page/line to start writhing from
void oled_page_select(uint8_t page);

//Make the screen white without deleting data stored in oled memory
void oled_white_screen();

//Select page/line and columb range, then fills the area with the byte val
void oled_set_value_range(uint8_t page,  uint8_t start, uint8_t end,uint8_t val);


//Clears the page and resets the memory that page
void oled_clear_page(uint8_t page);
//Clears the screen and resets the memory
void oled_clear_screen();

//Sets screen contrast
void oled_set_contrast(int8_t contrast_p);

//Writes a chesspattern to the screen
void oled_chess();

//Prints a character at last location at the given size
void oled_print_char_of_size(char letter,  uint8_t size);

//Prints a character of the last given size at the last location
uint8_t oled_print_char(char letter);


void oled_print_char_big_set_start(uint8_t x_pos, uint8_t y_pos);

//Prints a BIG caracher at a position set by oled_print_char_big_set_start
uint8_t oled_print_char_big(char letter);

//Set the size of the charactes used by printf
void oled_set_printf_size(uint8_t size);

//Sets the page used by printf
void oled_set_printf_page(uint8_t page);

//Sets printf to print inverted characters
void oled_printf_inverted();

//Sets printf to print noninverted characters
void oled_printf_normal();

//Maps printf to oled
static FILE oled_stream = FDEV_SETUP_STREAM(oled_print_char, NULL, _FDEV_SETUP_WRITE);

static FILE oled_big_stream = FDEV_SETUP_STREAM(oled_print_char_big, NULL, _FDEV_SETUP_WRITE);

#endif /* OLED_H_ */