/*
 * buttons.c
 *
 * Created: 26.09.2018 11:30:38
 *  Author: EdvardOlaf
 */

#include "push_buttons.h"

#define NUMB_BUTTONS 2

typedef struct Push_button {
  bool prev_state;
  bool state;
  int pin;
} Push_button;

Push_button buttons[NUMB_BUTTONS];

void push_buttons_init() {
  buttons[0].pin = PD4;
  buttons[1].pin = PD5;
  for (int i = 0; i < NUMB_BUTTONS; i++) {
    DDRD &= ~(1 << buttons[i].pin); // Set port to input
    buttons[i].prev_state = ((1 << buttons[i].pin) & PIND) != 0;
  }
}

void push_buttons_poll() {

  for (int i = 0; i < NUMB_BUTTONS; i++) {
    bool pushed = ((1 << buttons[i].pin) & PIND) != 0;
    if (pushed == 1 && buttons[i].prev_state == 0) {
      buttons[i].state = true;
    }
    buttons[i].prev_state = pushed;
  }
}

bool push_buttons_get_state(push_button_t button) {
  int temp = buttons[button].state;
  buttons[button].state = false;
  return temp;
}