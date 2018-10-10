/*
 * CAN_controller.c
 *
 * Created: 03.10.2018 13:53:49
 *  Author: torbjfug
 */ 

#include "CAN_controller.h"


//uint8_t CAN_transmit(const uint8_t * data, uint8_t data_size);
//void CAN_recive(uint16_t * address, uint8_t * data, uint8_t * data_size);

void CAN_init() {
	MCP2515_reset();
	
	uint8_t cmd[] = {MCP_RXBnCTRL_NOFILTER_bm};
	MCP2515_write(MCP_RXB0CTRL, cmd, 1); //Set to no filter
	
	MCP2515_bit_modify(MCP_CANINTE, 0b00000001,1); //Enable Interrupt on RX0
	
	MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, MODE_LOOPBACK);
	
	
}

uint16_t CAN_addres_construct(uint16_t number){
	return (number << CAN_ADDRESS_OFFSET)&CAN_ADDRESS_OFFSET_CONSTRUCT_bm;
}

uint16_t CAN_addres_read(uint16_t number){
	return (number << CAN_ADDRESS_OFFSET)&CAN_ADDRESS_OFFSET_READ_bm;
}

uint8_t CAN_transmit(const uint8_t * data, uint8_t data_size,uint16_t address) {
	//Check TXB0CTRL.TXREQ clear
	uint8_t TXREQ_data;
	MCP2515_read(MCP_TXB0CTRL, &TXREQ_data, 1); //Wait for transmit buffer is pending transmission
	while (TXREQ_data & (1 << TXBnCTRL_TXREQ)){ //to fix
		MCP2515_read(MCP_TXB0CTRL, &TXREQ_data, 1);
	}
	address = CAN_addres_construct(address);
	uint8_t address_8b[2];
	convert_from_16_to_8(address,address_8b);
	
	
	MCP2515_write(MCP_TXB0SIDH, address_8b, 2); //Set identifier to 0
	MCP2515_write(MCP_TXB0DLC, &data_size, 1); //Set data length

	
	MCP2515_write(MCP_TXB0D(0), data, data_size); //Write data to send
	MCP2515_rqt_send(0b001);
	volatile uint8_t status;
	_delay_us(100);
	MCP2515_read(MCP_TXB0CTRL, &status, 1);
	return status;
}

void CAN_recive(uint16_t * address, uint8_t * data, uint8_t * data_size) {
	uint8_t address_data[2];
	
	MCP2515_read(MCP_RXB0SIDH, address_data, 2); //Read identifier
	//*address = convert_from_8_to_16(address_data[0],address_data[1]);
	//*address = CAN_addres_read(*address);
	
	*address = (((uint16_t)address_data[0]) << 3) |  (((uint16_t)address_data[1]) >> 5);
	
	MCP2515_read(MCP_RXB0DLC, data_size, 1); //Read data size
	*data_size = (*data_size) & (0x0f); //map out the data length bits
	MCP2515_read(MCP_RXB0D(0), data, *data_size); //Read Data
	
	MCP2515_bit_modify(MCP_CANINTF, 0x01, 0x0); //Clear receive buffer int flag
}

void CAN_transmit_message(can_message* message){
	CAN_transmit(&(message->data),message->data_size,message->address);
}

void CAN_recive_message(can_message* message){
	CAN_recive(&(message->address),&(message->data),&(message->data_size));
}



void CAN_test() {
	uint8_t data[] = {44, 2, 5,12,4};
	CAN_transmit(data, 3,1);
	for (int i = 0;i < 10;i ++){
		data[0] = i;
		uint16_t add = 0;
		uint8_t r_data[1];
		CAN_transmit(data,1,0);
		uint8_t r_data_size = 0;
		CAN_recive(&add, r_data, &r_data_size);
		CAN_recive(&add, r_data, &r_data_size);
		printf("Sendt: %d	Recieved: %d \r\n",data[0],r_data[0]);
		
	}
	/*can_message message1;
	message1.address = 0xff0f;
	message1.data_size = 6;
	for (int i = 0; i < message1.data_size; i++){
		message1.data[i] = i+1;
	}
	
	can_message message2;
	message2.address = 0xff0f;
	message2.data_size = 3;
	for (int i = 0; i < message2.data_size; i++)
	{
		message2.data[i] = i+100;
	}
	
	CAN_transmit_message(&message1);
	CAN_transmit_message(&message2);
	
	can_message r_1;
	can_message r_2;
	r_1 = CAN_buffer_read();
	r_2 = CAN_buffer_read();
	
	printf("Sendt address: %u	Recieved ardess: %u \n\r",message1.address,r_1.address);
	printf("Sendt data_size: %d	Recieved size: %d \n\r",message1.data_size,r_1.data_size);
	for(int i = 0; i<message1.data_size; i++){
		printf("Sendt data: %d	Recieved data: %d \n\r",message1.data[i],r_1.data[i]);
	}
	
	printf("Sendt address: %u	Recieved ardess: %u \n\r",message2.address,r_2.address);
	printf("Sendt data_size: %d	Recieved size: %d \n\r",message2.data_size,r_2.data_size);
	for(int i = 0; i<message2.data_size; i++){
		printf("Sendt data: %d	Recieved data: %d \n\r",message2.data[i],r_2.data[i]);
	}*/
	
// 	uint16_t add = 0;
// 	uint8_t r_data[3];
// 	uint8_t r_data_size = 0;
// 	CAN_recive(&add, r_data, &r_data_size);
// 	printf("length: %d	data: %d %d %d	address: %d\n\r", r_data_size, r_data[0], r_data[1], r_data[2], add);
}