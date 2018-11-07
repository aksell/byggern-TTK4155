/*
 * oled_menu.h
 *
 * Created: 26.09.2018 08:46:04
 *  Author: torbjfug
 */ 


#ifndef OLED_MENU_H_
#define OLED_MENU_H_

#include "config.h"
#include <stdlib.h>
#include <util/delay.h>

#include "oled.h"
#include "utilities.h"
#include "joystick.h"
#include "push_buttons.h"
#include "ping_pong_loop.h"

typedef struct Menu_element_s Menu_element;
typedef struct Menu_s Menu;

void oled_menu_print(Menu * menu);
void oled_menu_print_current_menu();
void oled_menu_init();
void oled_menu_select_item();
void oled_menu_update();

void oled_menu_increment_score_value();
void oled_menu_reset_score_value();

void oled_menu_increment_current_value();

#endif /* OLED_MENUE_H_ */