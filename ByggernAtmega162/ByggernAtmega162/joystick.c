/*
 * joystick.c
 *
 * Created: 12.09.2018 14:52:39
 *  Author: EdvardOlaf
 */
#include "joystick.h"

#define JOYSTICK_DEAD_ZONE 10
#define NUM_AXIS 2

bool lowpass_enabled;
float alpha = 0.3;

volatile int8_t prev_value[NUM_AXIS];
volatile int8_t curr_value[NUM_AXIS];
volatile int8_t offset_value[NUM_AXIS];

void joystick_init(bool lowpass_enable) {
  lowpass_enabled = false;
  prev_value[0] = 0;
  prev_value[1] = 0;
  curr_value[0] = 0;
  curr_value[1] = 0;

  offset_value[0] = 127 - adc_read(1);
  offset_value[1] = 127 - adc_read(2);

  lowpass_enabled = lowpass_enable;
}

void joystick_poll_one_axis(joystick_axis_t joystick_axis_p) {
  int16_t value =
      adc_read(joystick_axis_p + 1) + offset_value[joystick_axis_p] - 127;

  if (value <= JOYSTICK_DEAD_ZONE && value >= -JOYSTICK_DEAD_ZONE) {
    value = 0;
  }

  if (value > 127) {
    value = 127;
  } else if (value < -127) {
    value = -127;
  }

  curr_value[joystick_axis_p] = (int8_t)value;
}

void joystick_poll() {
  joystick_poll_one_axis(JOYSTICK_X);
  joystick_poll_one_axis(JOYSTICK_Y);
}

volatile int8_t get_unfiltered_percent(joystick_axis_t joystick_axis_p) {
  return (int8_t)(((int16_t)(curr_value[joystick_axis_p]) * 100) / 128);
}

volatile int8_t joystick_get_percent(joystick_axis_t joystick_axis_p) {
  if (lowpass_enabled) {
    prev_value[joystick_axis_p] =
        (int8_t)(get_unfiltered_percent(joystick_axis_p) * alpha +
                 prev_value[joystick_axis_p] * (1.0 - alpha));
    return prev_value[joystick_axis_p];
  } else {
    return get_unfiltered_percent(joystick_axis_p);
  }
}

volatile int8_t joystick_get_value(joystick_axis_t joystick_axis_p) {
  if (lowpass_enabled) {
    prev_value[joystick_axis_p] = (curr_value[joystick_axis_p] * alpha +
                                   prev_value[joystick_axis_p] * (1.0 - alpha));
    return prev_value[joystick_axis_p];
  } else {
    return curr_value[joystick_axis_p];
  }
}

joystick_dir_t joystick_get_dir() {
  int8_t x_a = joystick_get_percent(JOYSTICK_X);
  int8_t y_a = joystick_get_percent(JOYSTICK_Y);

  if (x_a > 50)
    return RIGHT;
  if (x_a < -50)
    return LEFT;
  if (y_a > 50)
    return UP;
  if (y_a < -50)
    return DOWN;
  return NEUTRAL;
}
