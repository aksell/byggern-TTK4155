/*
 * main.c
 *
 * Created: 17.10.2018 09:26:45
 *  Author: EdvardOlaf
 */

#include "config.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#include "CAN_buffer.h"
#include "CAN_controller.h"
#include "dc_motor.h"
#include "internal_ADC.h"
#include "internal_ADC.h"
#include "music.h"
#include "solenoide.h"
#include "speaker.h"
#include "spi.h"
#include "state_machine.h"
#include "timer.h"
#include "uart.h"
#include "utilities.h"
#include "utilities.h"
int main(void) {
  servo_init_fast_pwm_3();
  uart_init();
  stdout = &uart_stream;
  spi_init();
  CAN_init();
  CAN_buffer_init();

  dac_init();

  dc_motor_init();
  ball_sensor_init();
  music_init();
  solenoide_init();
  state_machine_init();
  sei();

  // dc_motor_controller_enable();
  music_set_bpm(80);
  music_play_loop(GOT_MUSIC);
  printf("Hei\n\r");
  while (1) {
    // printf("2");
    // dac_write(-100);
    state_machine_update();
    //_delay_ms(10);
    /*
                    CAN_buffer_test_2();
                    bool C_buffer_empty= CAN_buffer_empty();
                    while(!C_buffer_empty){
                            message = CAN_buffer_read();
                            printf("\n\rAdd%d\n\r",message.address);
                            for(int i = 0;i<message.data_size;i++){
                                    printf(" %d",message.data[i]);
                            }
                            C_buffer_empty = CAN_buffer_empty();
                    }
                    _delay_ms(1000);
                    printf("Done");*/
  }
  return 0;
}
