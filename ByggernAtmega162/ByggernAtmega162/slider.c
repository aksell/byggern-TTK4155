/*
 * slider.c
 *
 * Created: 12.09.2018 17:17:08
 *  Author: akselsl
 */
#include "slider.h"
#define NUM_SLIDERS 2

slider_t sliders[NUM_SLIDERS];

uint8_t slider_get(slider_t slider) { return sliders[slider]; }

void slider_poll(slider_t slider) { sliders[slider] = adc_read(slider + 3); }
void sliders_poll() {
  slider_poll(SLIDER_LEFT);
  slider_poll(SLIDER_RIGHT);
}