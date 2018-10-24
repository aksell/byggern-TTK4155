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

void menu_print(Menu * menu);
void menu_print_current_menu();
void menu_init();
void menu_select_item();
void menu_update();

void menu_increment_score_value();
void menu_reset_score_value();

void menu_increment_current_value();

#endif /* OLED_MENUE_H_ */