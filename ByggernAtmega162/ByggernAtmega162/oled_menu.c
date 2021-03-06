/*
 * oled_menu.c
 *
 * Created: 26.09.2018 08:45:48
 *  Author: torbjfug
 */
#include "oled_menu.h"

#define MENU_LENGTH 8
#define MENU_TITLE_LENGTH 14

volatile struct Menu_element_s {
  char title[MENU_TITLE_LENGTH];
  Menu *child_menu;
  void (*element_func)(int);
  int8_t value;           //-127 means not applicable
  uint8_t increment_rate; // 0 means value can not be changed
};

volatile struct Menu_s {
  char title[MENU_TITLE_LENGTH];
  Menu_element menu_items[MENU_LENGTH];
  int selected_item;
};

// Save the menus in the external SRAM
Menu *oled_main_menu = (Menu *)SRAM_OFFSET;
Menu *oled_settings_menu = (Menu *)(SRAM_OFFSET + sizeof(Menu));
Menu *oled_credit_menu = (Menu *)(SRAM_OFFSET + sizeof(Menu) * 2);
Menu *oled_current_menu;

void oled_menu_set_parent(Menu *menu, Menu *parent) {
  if (parent != NULL) {
    menu->menu_items[0] = (Menu_element){"Back", parent, NULL, -127, 0};
  }
}

void oled_menu_element_print(Menu_element *menu_element) {
  if (menu_element->title[0] != NULL) { // Title exists
    printf(" ");
    printf("%s", menu_element->title);

    if (menu_element->value > -127) {
      printf(" %4i", menu_element->value);
    }
    printf("\n");
  }
}

void oled_menu_print(Menu *menu) {
  stdout = &oled_stream;
  oled_set_printf_page(0);
  oled_columb_range_select(0, OLED_COLUMBS);
  printf("%s\n", menu->title);
  for (int i = 0; i < MENU_LENGTH; i++) {
    if (i == menu->selected_item) { // Invert selected item
      oled_printf_inverted();
      oled_menu_element_print(&(menu->menu_items[i]));
      oled_printf_normal();
    } else {
      oled_menu_element_print(&(menu->menu_items[i]));
    }
  }
  stdout = &uart_stream;
}

void oled_menu_select_item() {
  if (oled_current_menu->menu_items[oled_current_menu->selected_item]
          .element_func != NULL) { // Element has assosiated function
    oled_current_menu->menu_items[oled_current_menu->selected_item]
        .element_func(
            oled_current_menu->menu_items[oled_current_menu->selected_item]
                .value);
  }
  if (oled_current_menu->menu_items[oled_current_menu->selected_item]
          .child_menu != NULL) { // Element has child
    oled_current_menu =
        (oled_current_menu->menu_items[oled_current_menu->selected_item]
             .child_menu);
    oled_clear_screen();
  }
}

void oled_menu_up() {
  for (int i = 0; i < MENU_LENGTH; i++) {
    oled_current_menu->selected_item =
        (oled_current_menu->selected_item - 1 + 6) %
        6; // Loop to top if at bottom of menu
    if (oled_current_menu->menu_items[oled_current_menu->selected_item]
            .title[0] != NULL) { // Check that the menu item exists
      break;
    }
  };
}

void oled_menu_down() {
  for (int i = 0; i < MENU_LENGTH; i++) {
    oled_current_menu->selected_item = (oled_current_menu->selected_item + 1) %
                                       6; // Loop to top if at bottom of menu
    if (oled_current_menu->menu_items[oled_current_menu->selected_item]
            .title[0] != NULL) { // Check that the menu item exists
      break;
    }
  }
}

void oled_menu_increment_value(Menu_element *menu_element) {
  if (menu_element->increment_rate != 0) { // Value can be changed
    if (menu_element->value >= (100 - menu_element->increment_rate)) {
      menu_element->value = 100;
    } else {
      menu_element->value += menu_element->increment_rate;
    }
  }
}

void oled_menu_decrement_value(
    Menu_element *menu_element) { // Value can be changed
  if (menu_element->increment_rate != 0) {
    if (menu_element->value <= -100 + menu_element->increment_rate) {
      menu_element->value = -100;
    } else {
      menu_element->value -= menu_element->increment_rate;
    }
  }
}

void oled_menu_set_value(Menu_element *menu_element,
                         int8_t val) { // Value can be changed
  if (menu_element->increment_rate != 0) {
    if (val < -100) {
      menu_element->value = -100;
    } else if (val > 100) {
      menu_element->value = 100;
    } else {
      menu_element->value = val;
    }
  }
}

void oled_menu_increment_current_value() {
  oled_menu_increment_value(
      &(oled_current_menu->menu_items[oled_current_menu->selected_item]));
}

void oled_menu_decrement_current_value() {
  oled_menu_decrement_value(
      &(oled_current_menu->menu_items[oled_current_menu->selected_item]));
}

void oled_menu_update() {
  if (timer1_done()) {
    joystick_dir_t dir = joystick_get_dir();
    if (dir == UP) {
      oled_menu_up();
    } else if (dir == DOWN) {
      oled_menu_down();
    } else if (dir == LEFT) {
      oled_menu_decrement_current_value();
    } else if (dir == RIGHT) {
      oled_menu_increment_current_value();
    }
    if (push_buttons_get_state(
            PUSH_BUTTON_RIGHT)) { // push button right button for select
      oled_menu_select_item();
    } else if (push_buttons_get_state(0)) { // Push left button for back
      if (oled_current_menu->menu_items[0].child_menu !=
          NULL) {                             // Not in main menu
        oled_current_menu->selected_item = 0; // go to back button
        oled_menu_select_item();
        oled_menu_print(oled_current_menu);
      }
    }

    oled_menu_print(oled_current_menu);
    timer1_reset();
  }
}

void oled_menu_back() {
  if (oled_current_menu->menu_items[0].child_menu !=
      NULL) {                             // Menu has a deffined parrent menu
    oled_current_menu->selected_item = 0; // go to back button at the top
    oled_menu_select_item();
    oled_menu_print(oled_current_menu);
  }
}

// Test program for oled menu. Set screen white for one second
void oled_menu_white_screen_game() {
  oled_white_screen();
  _delay_ms(1000);
  oled_menu_print(oled_current_menu);
}

void oled_menu_print_current_menu() { oled_menu_print(oled_current_menu); }

int8_t oled_menu_get_contrast() {
  return oled_settings_menu->menu_items[1].value;
}

void oled_menu_init() {
  *oled_main_menu = (Menu){
      .title = "MAIN MENU",
      .menu_items[0] =
          (Menu_element){"Play", NULL, state_machine_set_in_game, -127, 0},
      .menu_items[1] =
          (Menu_element){"Settings", oled_settings_menu, NULL, -127, 0},
      .menu_items[2] =
          (Menu_element){"Credits", oled_credit_menu, NULL, -127, 0},
      .menu_items[3] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .menu_items[4] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .menu_items[5] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .menu_items[6] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .menu_items[7] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .selected_item = 0};

  *oled_settings_menu = (Menu){
      .title = "SETTINGS",
      .menu_items[1] =
          (Menu_element){"Contrast", NULL, &oled_set_contrast, 0, 10},
      .menu_items[2] =
          (Menu_element){"Music", NULL, &state_machine_set_game_music, 0, 1},
      .menu_items[3] = (Menu_element){"RS High Score", NULL,
                                      &score_reset_high_score, -127, 0},
      .menu_items[4] = (Menu_element){"Cal Motor", NULL,
                                      &state_machine_calibrate_motor, -127, 0},
      .menu_items[5] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .menu_items[6] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .menu_items[7] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .selected_item = 0};
  oled_menu_set_parent(oled_settings_menu, oled_main_menu);

  *oled_credit_menu = (Menu){
      .title = "CREDITS",
      .menu_items[1] = (Menu_element){"Aksel Lenes,", NULL, NULL, -127, 0},
      .menu_items[2] = (Menu_element){"Edvard Grodem,", NULL, NULL, -127, 0},
      .menu_items[3] = (Menu_element){"Torbjorn", NULL, NULL, -127, 0},
      .menu_items[4] = (Menu_element){"Fuglestad", NULL, NULL, -127, 0},
      .menu_items[5] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .menu_items[6] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .menu_items[7] = (Menu_element){NULL, NULL, NULL, -127, 0},
      .selected_item = 0};
  oled_menu_set_parent(oled_credit_menu, oled_main_menu);

  oled_current_menu = oled_main_menu;
  oled_menu_print(oled_main_menu);
}