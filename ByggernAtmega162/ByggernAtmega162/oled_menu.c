/*
 * oled_menu.c
 *
 * Created: 26.09.2018 08:45:48
 *  Author: torbjfug
 */ 
#include "oled_menu.h"



struct Menu_element_s{
	char title[10];
	Menu * child_menu;
	void (*element_func)(int);
	int8_t value;			//-127 means not applicable
	uint8_t increment_rate;	//0 means value can not be changed 
};


struct Menu_s{
	char title[10];
	Menu_element menu_items[6];
	int selected_item;
};

Menu oled_main_menu;
Menu oled_settings_menu;
Menu oled_game_menu;
Menu oled_score_menu;
Menu *oled_current_menu;


void oled_menu_set_parent(Menu * menu, Menu * parent) {
	if(parent != NULL) {
		menu->menu_items[0] = (Menu_element) {"Back", parent, NULL,-127,0};
	}
}

void oled_menu_element_print(Menu_element * menu_element){
	if (menu_element->title[0] != NULL){ //Title exists
		printf(" ");
		printf("%s", menu_element->title);
		
		if(menu_element->value > -127){
			printf(" %i",menu_element->value);
		}
		printf("\n");
	}
}

void oled_menu_print(Menu * menu) {
	stdout = &oled_stream;
	oled_clear_screen();
	oled_set_printf_page(0);
	oled_columb_range_select(0,OLED_COLUMBS);
	printf("%s\n", menu->title);
	for (int i = 0;i<6;i++){
		if (i == menu->selected_item){ //Invert selected item
			oled_printf_inverted();
			oled_menu_element_print(&(menu->menu_items[i]));
			oled_printf_normal();
		}
		else{
			oled_menu_element_print(&(menu->menu_items[i]));
		}
	}
	//stdout = &uart_stream;
	
}

void oled_menu_select_item(){
	if (oled_current_menu->menu_items[oled_current_menu->selected_item].element_func != NULL){ //Element has assosiated function
		oled_current_menu->menu_items[oled_current_menu->selected_item].element_func(oled_current_menu->menu_items[oled_current_menu->selected_item].value);
	}
	if(oled_current_menu->menu_items[oled_current_menu->selected_item].child_menu != NULL) {//Element has child
		oled_current_menu = (oled_current_menu->menu_items[oled_current_menu->selected_item].child_menu);
		
	}		
}

void oled_menu_up(){
	for(int i = 0; i <8;i++){
		oled_current_menu->selected_item = (oled_current_menu->selected_item - 1 + 8) % 8;		//Loop to top if at bottom of menu
		if (oled_current_menu->menu_items[oled_current_menu->selected_item].title[0] != NULL){	//Check that the menu item exists
			break;
		}
	};
}

void oled_menu_down(){
	for(int i = 0; i <8;i++){
		oled_current_menu->selected_item = (oled_current_menu->selected_item + 1) % 8;			//Loop to top if at bottom of menu
		if (oled_current_menu->menu_items[oled_current_menu->selected_item].title[0] != NULL){	//Check that the menu item exists 
			break;
		}
	}
	
}


void oled_menu_increment_value(Menu_element * menu_element){
	if (menu_element->increment_rate != 0){ //Value can be changed
		if (menu_element->value >= (100-menu_element->increment_rate)){
			menu_element->value = 100;
		}
		else{
			menu_element->value += menu_element->increment_rate;
		}
	}
}

void oled_menu_decrement_value(Menu_element * menu_element){		//Value can be changed
	if (menu_element->increment_rate != 0){
		if (menu_element->value <= -100+menu_element->increment_rate){
			menu_element->value = -100;
		}
		else{
			menu_element->value -= menu_element->increment_rate;
		}
	}
}

void oled_menu_set_value(Menu_element * menu_element, int8_t val){		//Value can be changed
	if (menu_element->increment_rate != 0){
		if (val< -100){
			menu_element->value = -100;
		}
		else if(val > 100){
			menu_element->value = 100;
		}
		else{
			menu_element->value = val;
		}
	}
}

void oled_menu_set_score(int8_t val){
	oled_menu_set_value(&(oled_game_menu.menu_items[1]),val);
	oled_menu_set_value(&(oled_score_menu.menu_items[1]),val);
}


void oled_menu_increment_current_value(){
	oled_menu_increment_value(&(oled_current_menu->menu_items[oled_current_menu->selected_item]));
}

void oled_menu_decrement_current_value(){
	oled_menu_decrement_value(&(oled_current_menu->menu_items[oled_current_menu->selected_item]));
}

void oled_menu_display_stats(){
	oled_current_menu = &oled_score_menu;
	oled_menu_print_current_menu();
}




void oled_menu_update(){
	if(1 || timer1_done()){
		joystick_dir_t dir = joystick_get_dir();
		if(dir == UP){
			oled_menu_up();	
		}
		else if(dir == DOWN) {
			oled_menu_down();
		}
		else if(dir == LEFT) {
			oled_menu_decrement_current_value();
			oled_menu_print(oled_current_menu);

		}
		else if(dir == RIGHT) {
			oled_menu_increment_current_value();
		}
		if(push_buttons_get_state(PUSH_BUTTON_RIGHT)){//push button right button for select
			oled_menu_select_item();
		}
		else if(push_buttons_get_state(0)){//Push left button for back
			if(oled_current_menu->menu_items[0].child_menu != NULL){//Not in main menu
				oled_current_menu->selected_item = 0; //go to back button
				oled_menu_select_item();
				oled_menu_print(oled_current_menu);
			}
		}

		oled_menu_print(oled_current_menu);
		timer1_reset();	
	}
}



//Test program for oled menu. Set screen white for one second
void oled_menu_white_screen_game(){
	oled_white_screen();
	_delay_ms(1000);
	oled_menu_print(oled_current_menu);
}

void oled_menu_print_current_menu(){
	oled_menu_print(oled_current_menu);
}

void oled_menu_init() {
	oled_main_menu = (Menu) {
		.title = "MAIN MENU",
		//.menu_items[0] = (Menu_element) {"Play", NULL, &state_machine_set_next_state,IDLE,0},
		.menu_items[0] = (Menu_element) {"Play", NULL, state_machine_set_in_game,IDLE,0},
		.menu_items[1] = (Menu_element) {"Settings", &oled_settings_menu, NULL,-127,0},
		.menu_items[2] = (Menu_element) {"Test", NULL, NULL,-12,1},
		.menu_items[3] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[4] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[5] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.selected_item = 0
	};
	

	oled_settings_menu = (Menu) {
		.title = "SETTINGS",
		.menu_items[1] = (Menu_element) {"Brightness", NULL, NULL,0,10},
		.menu_items[2] = (Menu_element) {"Game Music", NULL, &state_machine_set_game_music,0,1},
		.menu_items[3] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[4] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[5] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.selected_item = 1
	};
	oled_menu_set_parent(&oled_settings_menu, &oled_main_menu);
	
	
	oled_game_menu = (Menu) {
		.title = "PLAYING",
		.menu_items[0] = (Menu_element) {"Abort game", &oled_main_menu, state_machine_set_next_state,MENU,0},
		.menu_items[1] = (Menu_element) {"Score", NULL, NULL,0,0},
		.menu_items[2] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[3] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[4] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[5] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.selected_item = 1
	};
	oled_score_menu = (Menu) {
		.title = "GAME OVER",
		.menu_items[0] = (Menu_element) {"Back", &oled_main_menu, state_machine_set_next_state,MENU,0},
		.menu_items[1] = (Menu_element) {"Score", NULL, NULL,0,0},
		.menu_items[2] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[3] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[4] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.menu_items[5] = (Menu_element) {NULL, NULL, NULL,-127,0},
		.selected_item = 1
	};
	oled_current_menu = &oled_main_menu;
	oled_menu_print(oled_current_menu);
	
}