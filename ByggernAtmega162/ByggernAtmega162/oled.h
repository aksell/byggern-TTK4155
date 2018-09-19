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

#include "fonts.h"


#include <util/delay.h>
#define OLED_PAGES 8
#define OLED_COLUMBS 128

#define OLED_COLUMB_SET 0x21
#define OLED_PAGE_SET 0x22




void oled_init();
void oled_columb_range_select(uint8_t start, uint8_t end);
void oled_page_select(uint8_t page);

void oled_white_screen();
void oled_set_value_range(uint8_t page,  uint8_t start, uint8_t end,uint8_t val);



void oled_clear_page(uint8_t page);
void oled_clear_screen();
void oled_white();
void oled_chess();

void oled_print_char_at_columb(char letter, uint8_t page, uint8_t size);
uint8_t oled_print_char(char letter);
void oled_set_printf_size(uint8_t size);
void oled_set_printf_page(uint8_t page);
uint8_t oled_printf_dummy_recieve();

static FILE oled_stream = FDEV_SETUP_STREAM(oled_print_char, NULL, _FDEV_SETUP_WRITE);

#endif /* OLED_H_ */