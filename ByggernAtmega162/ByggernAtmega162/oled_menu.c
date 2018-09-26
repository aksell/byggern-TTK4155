/*
 * oled_menu.c
 *
 * Created: 26.09.2018 08:45:48
 *  Author: torbjfug
 */ 
#include "oled_menu.h"



struct Menu_element_s{
	char title[16];
	Menu * child_menu;
	void (*element_func)(int);
	int8_t value;			//-127 means not applicable
	uint8_t increment_rate;	//0 means value can not be changed 
};


struct Menu_s{
	char title[16];
	Menu_element menu_items[8];
	int selected_item;
};

Menu main_menu;
Menu settings_menu;
Menu * current_menu;


void menu_set_parent(Menu * menu, Menu * parent) {
	if(parent != NULL) {
		menu->menu_items[0] = (Menu_element) {"Back", parent, NULL,-127,0};
	}
}

void menu_element_print(Menu_element * menu_element){
	if (menu_element->title[0] != NULL){ //Title exists
		printf(" ");
		printf("%s", menu_element->title);
		
		if(menu_element->value > -127){
			printf(" %i",menu_element->value);
		}
		printf("\n");
	}
}

void menu_print(Menu * menu) {
	oled_clear_screen();
	oled_set_printf_page(0);
	oled_columb_range_select(0,OLED_COLUMBS);
	printf("%s\n", menu->title);
	for (int i = 0;i<8;i++){
		if (i == menu->selected_item){ //Invert selected item
			oled_printf_inverted();
			menu_element_print(&(menu->menu_items[i]));
			oled_printf_normal();
			
		}
		else{
			menu_element_print(&(menu->menu_items[i]));
		}
	}
	
}

void menu_select_item(){
	if (current_menu->menu_items[current_menu->selected_item].element_func != NULL){ //Element has assosiated function
		current_menu->menu_items[current_menu->selected_item].element_func(current_menu->menu_items[current_menu->selected_item].value);
	}
	if(current_menu->menu_items[current_menu->selected_item].child_menu != NULL) {//Element has child
		current_menu = (current_menu->menu_items[current_menu->selected_item].child_menu);
		
	}		
}

void menu_up(){
	for(int i = 0; i <8;i++){
		current_menu->selected_item = (current_menu->selected_item - 1 + 8) % 8;		//Loop to top if at bottom of menu
		if (current_menu->menu_items[current_menu->selected_item].title[0] != NULL){	//Check that the menu item exists
			break;
		}
	};
}

void menu_down(){
	for(int i = 0; i <8;i++){
		current_menu->selected_item = (current_menu->selected_item + 1) % 8;			//Loop to top if at bottom of menu
		if (current_menu->menu_items[current_menu->selected_item].title[0] != NULL){	//Check that the menu item exists 
			break;
		}
	}
	
}


void menu_increment_value(Menu_element * menu_element){
	if (menu_element->increment_rate != 0){ //Value can be changed
		if (menu_element->value >= (100-menu_element->increment_rate)){
			menu_element->value = 100;
		}
		else{
			menu_element->value += menu_element->increment_rate;
		}
	}
}

void menu_decrement_value(Menu_element * menu_element){//Value can be changed
	if (menu_element->increment_rate != 0){
		if (menu_element->value <= -100+menu_element->increment_rate){
			menu_element->value = -100;
		}
		else{
			menu_element->value -= menu_element->increment_rate;
		}
	}
}

void menu_increment_current_value(){
	menu_increment_value(&(current_menu->menu_items[current_menu->selected_item]));
	//menu_increment_value(&settings_menu.menu_items[1]);
}

void menu_decrement_current_value(){
	menu_decrement_value(&(current_menu->menu_items[current_menu->selected_item]));
}
void menu_update(){
	if(timer_done()){
		if(joystick_get_dir() == UP){
			menu_up();
			menu_print(current_menu);
			timer_reset();
		}
		else if(joystick_get_dir() == DOWN) {
			menu_down();
			menu_print(current_menu);
			timer_reset();
		}
		else if(push_buttons_get_state(1)){//push button 1 for select
			menu_select_item();
			menu_print(current_menu);
			timer_reset();
		}
		else if(push_buttons_get_state(0)){
			if(current_menu->menu_items[0].child_menu != NULL){//Not in main menu
				current_menu->selected_item = 0;
				menu_select_item();
				menu_print(current_menu);
				timer_reset();
			}
		}
		else if(joystick_get_dir() == LEFT) {
			menu_decrement_current_value();
			menu_print(current_menu);
			timer_reset();
		}
		else if(joystick_get_dir() == RIGHT) {
			menu_increment_current_value();
			menu_print(current_menu);
			timer_reset();
		}
		
	}
}



//Test program for oled menu. Set screen white for one second
void menu_white_screen_game(){
	oled_white_screen();
	_delay_ms(1000);
	menu_print(current_menu);
}

void menu_print_current_menu(){
	menu_print(current_menu);
}

void menu_init() {
	main_menu = (Menu) {
		.title = "MAIN MENU",
		.menu_items[0] = (Menu_element) {"Play", NULL, &menu_white_screen_game,-127,0},
		.menu_items[1] = (Menu_element) {"Settings", &settings_menu, NULL,-127,0},
		.menu_items[2] = (Menu_element) {"Test", NULL, NULL,-12,1},
		.menu_items[3] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[4] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[5] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[6] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[7] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.selected_item = 0,
	};
	
	
	
	
	settings_menu = (Menu) {
		.title = "SETTINGS",
		.menu_items[1] = (Menu_element) {"Brightness", NULL, NULL,0,10},
		.menu_items[2] = (Menu_element) {"Test", NULL, NULL,-127,0},
		.menu_items[3] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[4] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[5] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[6] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[7] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.selected_item = 1};
	
	menu_set_parent(&settings_menu, &main_menu);
	current_menu = &main_menu;
	menu_print(current_menu);
	
}