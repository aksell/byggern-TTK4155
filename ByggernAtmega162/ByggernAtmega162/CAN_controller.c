/*
 * CAN_controller.c
 *
 * Created: 03.10.2018 13:53:49
 *  Author: torbjfug
 */ 

#include "CAN_controller.h"

void CAN_init() {
	MCP2515_reset();
	
	uint8_t cmd[] = {MCP_RXBnCTRL_NOFILTER_bm};
	MCP2515_write(MCP_RXB0CTRL, cmd, 1); //Set to no filter
	
	MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, MODE_LOOPBACK);
	
	
}

uint8_t CAN_transmit(const uint8_t * data, uint8_t data_size) {
	//Check TXB0CTRL.TXREQ clear
	uint8_t TXREQ_data;
	MCP2515_read(MCP_TXB0CTRL, &TXREQ_data, 1); //Wait for transmit buffer is pending transmission
	while (TXREQ_data & (1 << TXBnCTRL_TXREQ)){ //to fix
		MCP2515_read(MCP_TXB0CTRL, &TXREQ_data, 1);
	}
	uint8_t address[] = {0, 0};
	MCP2515_write(MCP_TXB0SIDH, address, 2); //Set identifier to 0
	MCP2515_write(MCP_TXB0DLC, &data_size, 1); //Set data length

	
	MCP2515_write(MCP_TXB0D(0), data, data_size); //Write data to send
	MCP2515_rqt_send(0b001);
	volatile uint8_t status;
	MCP2515_read(MCP_TXB0CTRL, &status, 1);
	return status;
}

void CAN_recive(uint16_t * address, uint8_t * data, uint8_t * data_size) {
	uint8_t address_data[2];
	
	MCP2515_read(MCP_RXB0SIDH, address_data, 2); //Read identifier
	address = (address_data[0] << 2) |  (address_data[1] >> 5);
	
	MCP2515_read(MCP_RXB0DLC, data_size, 1); //Read data size
	*data_size = (*data_size) & (0x0f); //map out the data length bits
	MCP2515_read(MCP_RXB0D(0), data, *data_size); //Read Data //to fix size
	
	MCP2515_bit_modify(MCP_CANINTF, 0x01, 0x0); //Clear receive buffer int flag
}

void CAN_test() {
	uint8_t data[] = {44, 2, 5};
	CAN_transmit(data, 3);
	for (int i = 0;i < 10;i ++){
		data[0] = i;
		uint16_t add = 0;
		uint8_t r_data[1];
		CAN_transmit(data,1);
		uint8_t r_data_size = 0;
		CAN_recive(&add, r_data, &r_data_size);
		CAN_recive(&add, r_data, &r_data_size);
		printf("Sendt: %d	Recieved: %d \r\n",data[0],r_data[0]);
		
	}
// 	uint16_t add = 0;
// 	uint8_t r_data[3];
// 	uint8_t r_data_size = 0;
// 	CAN_recive(&add, r_data, &r_data_size);
// 	printf("length: %d	data: %d %d %d	address: %d\n\r", r_data_size, r_data[0], r_data[1], r_data[2], add);
}