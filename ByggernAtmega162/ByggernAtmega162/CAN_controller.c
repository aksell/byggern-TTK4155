/*
 * CAN_controller.c
 *
 * Created: 03.10.2018 13:53:49
 *  Author: torbjfug
 */

#include "CAN_controller.h"

// uint8_t CAN_transmit(const uint8_t * data, uint8_t data_size);
// void CAN_recive(uint16_t * address, uint8_t * data, uint8_t * data_size);

void CAN_init() {
  MCP2515_init();
  uint8_t cmd[] = {MCP_RXBnCTRL_NOFILTER_bm};
  MCP2515_write(MCP_RXB0CTRL, cmd, 1); // Set to no filter

  MCP2515_bit_modify(MCP_CANINTE, 0b00000001, 1); // Enable Interrupt on RX0

  MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, MODE_NORMAL);
}

uint16_t CAN_addres_construct(uint16_t number) {
  return (number << CAN_ADDRESS_OFFSET) & CAN_ADDRESS_OFFSET_CONSTRUCT_bm;
}

uint16_t CAN_addres_read(uint16_t number) {
  return (number << CAN_ADDRESS_OFFSET) & CAN_ADDRESS_OFFSET_READ_bm;
}

can_message CAN_message_construct(uint16_t address, uint8_t data_size,
                                  uint8_t *data) {
  can_message message;
  message.address = address;
  message.data_size = data_size;
  for (int i = 0; i < data_size; i++) {
    message.data[i] = data[i];
  }
  return message;
}

uint8_t CAN_transmit(const uint8_t *data, uint8_t data_size, uint16_t address) {
  // Check TXB0CTRL.TXREQ clear
  uint8_t TXREQ_data;
  MCP2515_read(MCP_TXB0CTRL, &TXREQ_data,
               1); // Wait for transmit buffer is pending transmission
  int read_errors = 0;
  while (TXREQ_data & (1 << TXBnCTRL_TXREQ)) { // toFix
    MCP2515_read(MCP_TXB0CTRL, &TXREQ_data, 1);
    if (read_errors++ > 10) {
      stdout = &uart_stream;
      printf("ERROR: Could not make contact with MPC2515\n\r");
      return 0xff;
    }
  }
  address = CAN_addres_construct(address);
  uint8_t address_8b[2];
  convert_from_16_to_8(address, address_8b);

  MCP2515_write(MCP_TXB0SIDH, address_8b, 2); // Set identifier to 0
  MCP2515_write(MCP_TXB0DLC, &data_size, 1);  // Set data length

  MCP2515_write(MCP_TXB0D(0), data, data_size); // Write data to send
  MCP2515_rqt_send(0b001);
  volatile uint8_t status;
  _delay_us(200);
  MCP2515_read(MCP_TXB0CTRL, &status, 1);
  return status;
}

void CAN_recive(uint16_t *address, uint8_t *data, uint8_t *data_size) {
  uint8_t address_data[2];

  MCP2515_read(MCP_RXB0SIDH, address_data, 2); // Read identifier
  //*address = convert_from_8_to_16(address_data[0],address_data[1]);
  //*address = CAN_addres_read(*address);

  *address =
      (((uint16_t)address_data[0]) << 3) | (((uint16_t)address_data[1]) >> 5);

  MCP2515_read(MCP_RXB0DLC, data_size, 1);      // Read data size
  *data_size = (*data_size) & (0x0f);           // map out the data length bits
  MCP2515_read(MCP_RXB0D(0), data, *data_size); // Read Data

  MCP2515_bit_modify(MCP_CANINTF, 0x01, 0x0); // Clear receive buffer int flag
}

void CAN_transmit_message(can_message *message) {
  CAN_transmit(&(message->data), message->data_size, message->address);
}

void CAN_recive_message(can_message *message) {
  CAN_recive(&(message->address), &(message->data), &(message->data_size));
}

void CAN_interrupt_routine() {
  can_message message;
  CAN_recive_message(&message);                 // Read message
  CAN_buffer_write(&message);                   // Write message to buffer
  MCP2515_bit_modify(MCP_CANINTF, (1 << 0), 0); // Set interrupt bit low
}

void interrupt0_init() {

  DDRD &= ~(1 << PD2); // Set port D pin 2
  cli();
  GICR |= 1 << INT0;   // Enable INT0
  MCUCR |= 1 << ISC01; //| 1<<ISC00;	// Trigger INT0 on falling edge
  sei();
}

ISR(INT0_vect) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { CAN_interrupt_routine(); }
}

void CAN_test() {
  stdout = &uart_stream;

  uint8_t data[] = {45, 3, 6, 13, 5};
  printf("Hei");
  for (int i = 0; i < 4; i++) {
    printf("HWI");
    uint16_t add = 10;
    uint8_t r_data[8];
    CAN_transmit(&(data[i]), 2, 1);
    uint8_t r_data_size = 0;
    CAN_recive(&add, r_data, &r_data_size);
    printf("Sendt: %d	Recieved: %d \r\n", data[i], r_data[0]);
  }
}