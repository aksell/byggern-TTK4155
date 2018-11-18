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
#include "uart.h"
#include "utilities.h"
#include "joystick.h"
#include "push_buttons.h"
#include "ping_pong_loop.h"
#include "state_machine.h"

typedef struct Menu_element_s Menu_element;
typedef struct Menu_s Menu;


//Initialize the oled menu
void oled_menu_init();

//Prints the menu on the oled screen
void oled_menu_print(Menu * menu);

//Print the menu that last selected 
void oled_menu_print_current_menu();

//When this function is called the selected item in the current menu runs 
//its function and if the item is a pointer to a new menu, that menu is set as current menu
void oled_menu_select_item();
void oled_menu_update();

//Set score in game menu
void oled_menu_set_score(int8_t val);

//Go to game over menu
void oled_menu_display_stats();

//Increments the selected item in the menu with 1
void oled_menu_increment_current_value();

//Decrements the selected item in the menu with 1
void oled_menu_decrement_current_value();

//Go back to parent menu
void oled_menu_back();


int8_t oled_menu_get_contrast();
#endif /* OLED_MENU_H_ */