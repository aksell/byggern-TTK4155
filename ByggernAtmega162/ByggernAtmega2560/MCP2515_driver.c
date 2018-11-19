/*
 * MCP2515_driver.c
 *
 * Created: 03.10.2018 11:04:40
 *  Author: EdvardOlaf
 */

#include "MCP2515_driver.h"

void MCP2515_read(uint8_t address, uint8_t *data, uint8_t data_size) {
  uint8_t packet_length = data_size + 2;
  uint8_t send_data[MAX_CAN_LENGTH];
  uint8_t receive_data[MAX_CAN_LENGTH];
  send_data[0] = MCP_READ;
  send_data[1] = address;

  spi_transmit_recieve(send_data, receive_data, packet_length);
  for (int i = 2; i < packet_length; i++) {
    data[i - 2] = receive_data[i];
  }

  // CS LOW
  // Send MCP_READ
  // Send 8 bit address
  // Read MISO pin
  // Adress in indremented
  // OPT: read more
  // CS LOW
}

void MCP2515_write(uint8_t address, const uint8_t *data, uint8_t data_size) {
  uint8_t packet_length = data_size + 2;
  uint8_t send_data[MAX_CAN_LENGTH];
  send_data[0] = MCP_WRITE;
  send_data[1] = address;
  for (int i = 2; i < packet_length; i++) {
    send_data[i] = data[i - 2];
  }
  spi_transmit(send_data, packet_length);

  // CS LOW
  // Send MCP_WRITE
  // Send address
  // Send Data
  // OPT: Send more data
  // CS high
}

void MCP2515_rqt_send(uint8_t TXBn_mask) {
  uint8_t cmd[] = {MCP_RTS(TXBn_mask)};
  spi_transmit(cmd, 1);
  // CS_LOW
  // SEND MCP_RTS( TXBn )
  // CS_HIGH
}

uint8_t MCP2515_read_status() {
  uint8_t read_data[2];
  uint8_t cmd[] = {MCP_READ_STATUS, 0xFF};
  spi_transmit_recieve(cmd, read_data, 2);
  return read_data[1];

  // CS_LOW
  // Send MCP_READ_STATUS
  // Read 8bit data
  // CS_low
}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
  uint8_t bts[] = {MCP_BITMOD, address, mask, data};
  spi_transmit(bts, 4);

  // CS LOW
  // Send MCP_BIT_MODIFY
  // Send Address
  // Send Mask
  // Send data
  // CS HIGH
}

void MCP2515_reset() {
  uint8_t cmd[] = {MCP_RESET};
  spi_transmit(cmd, 1);

  // CS LOW
  // Send MCP_RESET
  // CS HIGH
}