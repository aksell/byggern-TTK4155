/*
 * state_machine.c
 *
 * Created: 07.11.2018 18:29:31
 *  Author: torbjfug
 */
#include "state_machine.h"

#define SOLENOIDE_TRIGGER_TIME_MS 100

state_t state_machine_state;
state_t state_machine_next;

bool stop_game_ack_recieved;

uint8_t game_music;
uint8_t game_over_music;

void transmit_single_game_music_message(uint8_t song); // Forward

void state_machine_init() {
  state_machine_state = MENU;
  state_machine_next = MENU;
  game_music = 1;
  game_over_music = 3;
  stop_game_ack_recieved = false;
  timer3_init();
}

void state_machine_set_next_state(state_t next_state) {
  state_machine_next = next_state;
}

void state_machine_set_game_music(uint8_t song) {
  game_music = song;
  transmit_single_game_music_message(song);
}

void state_machine_set_game_over_music(uint8_t song) {
  game_over_music = song;
  transmit_single_game_music_message(song);
}

// CAN message transmissions
void transmit_single_game_music_message(uint8_t song) {
  can_message message;
  message = CAN_message_construct(CAN_START_MUSIC, 1, &song);
  CAN_transmit_message(&message);
}

void transmit_loop_game_music_message(uint8_t song) {
  can_message message;
  message = CAN_message_construct(CAN_START_MUSIC_LOOP, 1, &song);
  CAN_transmit_message(&message);
}

void transmit_music_stop() {
  can_message message;
  message = CAN_message_construct(CAN_STOP_MUSIC, 1, &game_music);
  CAN_transmit_message(&message);
}

void transmit_pos_message() {
  uint8_t data = 255 - slider_get(SLIDER_RIGHT);
  can_message message;
  message = CAN_message_construct(CAN_MOTOR_POS, 1, &data);
  CAN_transmit_message(&message);
}

void transmit_calibrate_motor_message() {
  can_message message;
  message = CAN_message_construct(CAN_MOTOR_CALIBRATE, 1, &game_music);
  CAN_transmit_message(&message);
}

void transmit_servo_pos_message() {
  uint8_t data = joystick_get_value(JOYSTICK_X);
  can_message message;
  message = CAN_message_construct(CAN_SERVO_POS, 1, &data);
  CAN_transmit_message(&message);
}

void transmit_solenoide_pos_message() {
  if (push_buttons_get_state(PUSH_BUTTON_RIGHT)) {
    uint16_t trigger_time = SOLENOIDE_TRIGGER_TIME_MS;
    uint8_t data[2];
    convert_from_16_to_8(trigger_time, data);
    can_message message;
    message = CAN_message_construct(CAN_SOLANOIDE_TRIGGER_MS, 2, data);
    CAN_transmit_message(&message);
  }
}

void transmit_start_game_message() {
  uint8_t data = 1;
  can_message message;
  message = CAN_message_construct(CAN_START_GAME, 1, &data);
  CAN_transmit_message(&message);
  // printf("A\n\r");
}

void transmit_end_game_message() {
  uint8_t data = 1;
  can_message message;
  message = CAN_message_construct(CAN_GAME_OVER, 0, &data);
  CAN_transmit_message(&message);
}

// State transmit functions

void in_game_CAN_transmit() {
  transmit_solenoide_pos_message();
  transmit_servo_pos_message();
  transmit_pos_message();
}

void display_stats_CAN_transmit() {
  if (!stop_game_ack_recieved) {
    transmit_end_game_message();
  }
}

void game_over_CAN_transmit() {
  if (!stop_game_ack_recieved) {
    transmit_end_game_message();
  }
}
// State update functions

/*
Poll IO needed for menu navigation
Update oled menu
*/

void menu_state_update() {
  if (timer3_done()) { // Check poling frequency for IO
    joystick_poll();
    push_buttons_poll();
    if (!stop_game_ack_recieved) {
      transmit_end_game_message();
    }
    timer3_reset();
  }
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
    if (push_buttons_get_state(PUSH_BUTTON_LEFT)) {
      stdout = &uart_stream;
      oled_menu_back();
    } else if (push_buttons_get_state(
                   PUSH_BUTTON_RIGHT)) { // push button right button for select
      oled_menu_select_item();
    }
    oled_menu_print_current_menu();
    timer1_reset();
  }
}

/*
Poll button while waiting for player to confirm or abort game start
*/
void idle_state_update() {
  if (timer3_done()) {
    push_buttons_poll();
    if (push_buttons_get_state(PUSH_BUTTON_LEFT)) {
      state_machine_next = MENU;
    }
    transmit_start_game_message();
    timer3_reset();
  }
  if (timer1_done()) {
    oled_menu_print_current_menu();
    timer1_reset();
  }
}

/*
Poll user input for game
*/
void in_game_update() {
  if (timer3_done()) { // Check poling frequency for IO
    joystick_poll();
    push_buttons_poll();
    sliders_poll();
    in_game_CAN_transmit();
    timer3_reset();
  }
  if (timer1_done()) {
    if (push_buttons_get_state(0)) {
      state_machine_next = GAME_OVER;
    }

    timer1_reset();
  }

  if (score_is_screen_outdated()) {
    score_screen_update();
  }
}
void game_over_update() {
  if (timer3_done()) {
    push_buttons_poll();
    game_over_CAN_transmit();
    timer3_reset();
  }

  if (timer1_done()) {
    if (push_buttons_get_state(PUSH_BUTTON_LEFT)) {
      state_machine_next = DISPLAY_STATS;
    } else if (push_buttons_get_state(
                   PUSH_BUTTON_RIGHT)) { // push button right button for select
      state_machine_next = DISPLAY_STATS;
    }
    timer1_reset();
  }
}

void display_stats_update() {

  if (timer3_done()) {
    push_buttons_poll();
    display_stats_CAN_transmit();
    timer3_reset();
  }
  if (timer1_done()) {
    if (push_buttons_get_state(PUSH_BUTTON_LEFT)) {
      state_machine_next = MENU;
      oled_menu_back();
    } else if (push_buttons_get_state(
                   PUSH_BUTTON_RIGHT)) { // push button right button for select
      state_machine_next = MENU;
      oled_menu_back();
    }
    timer1_reset();
  }
}

// State CAN receive functions
void menu_CAN_recieve() {
  volatile can_message message;
  bool buffer_empty = CAN_buffer_empty();
  while (!buffer_empty) {
    message = CAN_buffer_read();
    switch (message.address) {
    case CAN_GAME_OVER_ACK:
      stop_game_ack_recieved = true;
      break;
    default:
      break;
    }
    buffer_empty = CAN_buffer_empty();
  }
}

void idle_state_CAN_recieve() {
  can_message message;
  bool buffer_empty = CAN_buffer_empty();
  while (!buffer_empty) {
    message = CAN_buffer_read();
    switch (message.address) {
    case CAN_START_GAME_ACK:
      state_machine_next = IN_GAME;
      break;
    default:
      break;
    }
    buffer_empty = CAN_buffer_empty();
  }
}

void in_game_can_recieve() {
  volatile can_message message;
  bool buffer_empty = CAN_buffer_empty();
  while (!buffer_empty) {
    message = CAN_buffer_read();
    switch (message.address) {
    case CAN_BALL_SENSOR_TRIGGERED:
      state_machine_next = GAME_OVER;
      break;
    default:
      break;
    }
    buffer_empty = CAN_buffer_empty();
  }
}
void game_over_CAN_recieve() {
  volatile can_message message;
  bool buffer_empty = CAN_buffer_empty();
  while (!buffer_empty) {
    message = CAN_buffer_read();
    switch (message.address) {
    case CAN_GAME_OVER_ACK:
      stop_game_ack_recieved = true;
      break;
    default:
      break;
    }
    buffer_empty = CAN_buffer_empty();
  }
}

void display_stats_CAN_recieve() {
  volatile can_message message;
  bool buffer_empty = CAN_buffer_empty();
  while (!buffer_empty) {
    message = CAN_buffer_read();
    switch (message.address) {
    case CAN_GAME_OVER_ACK:
      stop_game_ack_recieved = true;
      break;
    default:
      break;
    }
    buffer_empty = CAN_buffer_empty();
  }
}

// State transition functions
void sc_menu_to_idle() {
  stdout = &uart_stream;
  printf("IDLE\n\r");
  score_screen_init();
  transmit_start_game_message();
}

void sc_idle_to_in_game() {

  stdout = &uart_stream;
  printf("IN GAME\n\r");
  score_reset();
  score_screen_init();
  transmit_loop_game_music_message(game_music);
  score_start_counting();
}

void sc_idle_to_menu() {
  stdout = &uart_stream;
  transmit_loop_game_music_message(game_music);
  printf("MENU\n\r");
  score_stop_counting();
  transmit_music_stop();
  stop_game_ack_recieved = false;
}

void sc_in_game_to_menu() {
  stdout = &uart_stream;
  printf("MENU\n\r");
  score_stop_counting();
  oled_clear_screen();
  oled_menu_back();
  stop_game_ack_recieved = false;
  transmit_music_stop();
}

void sc_ingame_to_game_over() {

  score_stop_counting();

  // Display Game Over
  transmit_loop_game_music_message(game_over_music); // Play game over music

  oled_clear_screen();
  oled_set_contrast(-127);
  stdout = &oled_big_stream;
  oled_print_char_big_set_start(0, 0);
  printf("GAME");
  oled_print_char_big_set_start(0, 4);
  printf("OVER");

  stdout = &uart_stream;
  printf("GAME OVER\n\r");
  stop_game_ack_recieved = false;
}

void sc_display_stats_to_menu() {
  stdout = &uart_stream;
  printf("MENU f disp\n\r");
  stop_game_ack_recieved = false;
  oled_clear_screen();
}

void sc_game_over_to_stats() {
  oled_set_contrast(oled_menu_get_contrast());
  stdout = &uart_stream;
  printf("STATS\n\r");
  score_high_score_display_init();
}

void state_machine_update() {
  switch (state_machine_state) {
  case MENU:
    menu_state_update();
    menu_CAN_recieve();
    switch (state_machine_next) {
    case IDLE:
      sc_menu_to_idle();
      state_machine_state = IDLE;
      break;
    default:
      break;
    }
    break;
  case IDLE:
    idle_state_update();
    idle_state_CAN_recieve(); // Wait for ACK from node 2

    switch (state_machine_next) {
    case MENU:
      sc_idle_to_menu();
    case IN_GAME:
      stdout = &uart_stream;
      sc_idle_to_in_game();
      state_machine_state = IN_GAME;
      break;
    default:
      break;
    }
    break;
  case IN_GAME:
    in_game_update();
    in_game_can_recieve();
    switch (state_machine_next) {
    case MENU:
      sc_in_game_to_menu();
      state_machine_state = MENU;
      break;
    case GAME_OVER:
      sc_ingame_to_game_over();
      state_machine_state = GAME_OVER;
      break;
    default:
      break;
    }
    break;

  case GAME_OVER:
    game_over_CAN_recieve();
    game_over_update();
    switch (state_machine_next) {
    case DISPLAY_STATS:
      sc_game_over_to_stats();
      state_machine_state = DISPLAY_STATS;
      break;
    default:
      break;
    }
    break;
  case DISPLAY_STATS:
    display_stats_CAN_recieve();
    display_stats_update();
    switch (state_machine_next) {
    case MENU:
      sc_display_stats_to_menu();
      state_machine_state = MENU;
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void state_machine_set_in_game(int dummy_int) {
  state_machine_set_next_state(IDLE);
}

void state_machine_calibrate_motor(int dummy_int) {
  transmit_calibrate_motor_message();
}