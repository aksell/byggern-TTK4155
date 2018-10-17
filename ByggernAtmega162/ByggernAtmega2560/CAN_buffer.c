/*
 * CAN_buffer.c
 *
 * Created: 10.10.2018 09:26:12
 *  Author: torbjfug
 */ 

#include "CAN_buffer.h"

uint8_t buffer_data[CAN_BUFFER_SIZE];
uint8_t head;
uint8_t tail;

void CAN_buffer_init(){
	head = 0;
	tail = head;
	
	for(int i = 0; i<CAN_BUFFER_SIZE; i++){
		buffer_data[i] = 0;
	}
	
}

void CAN_buffer_increment_head(){
	head = (head + 1) % CAN_BUFFER_SIZE;
}

void CAN_buffer_increment_tail(){
	tail = (tail + 1) % CAN_BUFFER_SIZE;
}

void CAN_buffer_write(can_message *message){
	uint8_t adress_array[2] = {0,0};
	convert_from_16_to_8(message->address,adress_array);
	buffer_data[head] = adress_array[0];
	CAN_buffer_increment_head();
	buffer_data[head] = adress_array[1];
	CAN_buffer_increment_head();
	buffer_data[head] = message->data_size;
	CAN_buffer_increment_head();
	for (int i = 0; i < message->data_size; i++){
		buffer_data[head] = message->data[i];
		CAN_buffer_increment_head();
	}
}

can_message CAN_buffer_read(){
	can_message message;
	if(tail < CAN_BUFFER_SIZE-1){
		message.address = convert_from_8_to_16(buffer_data[tail],buffer_data[tail+1]);
		CAN_buffer_increment_tail();
		CAN_buffer_increment_tail();
	}
	else{
		message.address = convert_from_8_to_16(buffer_data[tail], buffer_data[0]);
		tail = 1;
	}
	message.data_size = buffer_data[tail];
	CAN_buffer_increment_tail();
	
	for(int i = 0; i<message.data_size ; i++){
		message.data[i] = buffer_data[tail];
		CAN_buffer_increment_tail();
	}
	return message;
	
}




void CAN_buffer_test(){
	can_message message1;
	message1.address = 17;
	message1.data_size = 7;
	for (int i = 0; i < message1.data_size; i++)
	{
		message1.data[i] = i+1;
	}
	
	can_message message2;
	message2.address = 0xff0f;
	message2.data_size = 3;
	for (int i = 0; i < message2.data_size; i++)
	{
		message2.data[i] = i+100;
	}
	
	can_message read_message_1;
	read_message_1.address = 0;
	read_message_1.data_size = 0;
	for (int i = 0; i<8;i++){
		read_message_1.data[i] = 0;
	}
	
	can_message read_message_2;
	read_message_2.address = 0;
	read_message_2.data_size = 0;
	for (int i = 0; i<8;i++){
		read_message_2.data[i] = 0;
	}
	
	CAN_buffer_write(&message1);
	CAN_buffer_write(&message2);
	
	read_message_1 = CAN_buffer_read();
	read_message_2 = CAN_buffer_read();
	
	
	printf("Message 1:\n\r");
	printf("Sendt address: %u	Recieved ardess: %u \n\r",message1.address,read_message_1.address);
	printf("Sendt data_size: %d	Recieved size: %d \n\r",message1.data_size,read_message_1.data_size);
	for(int i = 0; i<message1.data_size; i++){
		printf("Sendt data: %d	Recieved data: %d \n\r",message1.data[i],read_message_1.data[i]);
	}
	
	printf("Message 2:\n\r");
	printf("Sendt address: %u	Recieved ardess: %u \n\r",message2.address,read_message_2.address);
	printf("Sendt data_size: %d	Recieved size: %d \n\r",message2.data_size,read_message_2.data_size);
	for(int i = 0; i<message2.data_size; i++){
		printf("Sendt data: %d	Recieved data: %d \n\r",message2.data[i],read_message_2.data[i]);
	}
	
}

bool CAN_buffer_is_empty(){
	return head == tail;
}

void CAN_buffer_test_2(){
	can_message message1;
	message1.address = 0x7A1;
	message1.data_size = 2;
	for (int i = 0; i < message1.data_size; i++){
		message1.data[i] = i+120;
	}
	
	printf("Hei");
	CAN_transmit_message(&message1);
	//_delay_ms(100);
	//CAN_transmit_message(&message2);
	CAN_transmit_message(&message1);
	//_delay_ms(100);
	//CAN_transmit_message(&message2);
	
	
	
	can_message r_2;
	r_2.address = 1;
	r_2.data_size = 0;
	for (int i = 0; i<8;i++){
		r_2.data[i] = 0;
	}
	
	while(!CAN_buffer_is_empty()){
		r_2 = CAN_buffer_read();
		printf("Sendt address: %x	Recieved ardess: %x \n\r",message1.address,r_2.address);
		printf("Sendt data_size: %d	Recieved size: %d \n\r",message1.data_size,r_2.data_size);
		for(int i = 0; i<r_2.data_size; i++){
			printf("Sendt data: %d	Recieved data: %d \n\r",message1.data[i],r_2.data[i]);
		}
	}
	
	
}