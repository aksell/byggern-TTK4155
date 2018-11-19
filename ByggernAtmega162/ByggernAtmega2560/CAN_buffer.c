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
bool buffer_empty;

void CAN_buffer_init(){
	head = 0;
	tail = head;
	buffer_empty = true;
	for(int i = 0; i<CAN_BUFFER_SIZE; i++){
		buffer_data[i] = 0;
	}
	
}

void CAN_buffer_increment_head(){
	head = (head + 1) % CAN_BUFFER_SIZE;
	if(head != tail){
		buffer_empty = false;
	}
}

void CAN_buffer_increment_tail(){
	tail = (tail + 1) % CAN_BUFFER_SIZE;
	if(tail == head){
		buffer_empty = true;
	}
}

uint8_t CAN_buffer_remaining_size(){
	if(!buffer_empty && head == tail){
		return 0;
	}
	else if (head >= tail) {
		uint8_t val = (uint8_t)(CAN_BUFFER_SIZE - head + tail);
		
		return val;
	}
	else {
		uint8_t val = tail-head;
		return val;
	}
}


bool CAN_buffer_empty(){
	return buffer_empty;
}


void CAN_buffer_flush(){
	CAN_buffer_init();
}


void CAN_buffer_write(can_message *message){
	uint8_t remaning_size = CAN_buffer_remaining_size();
	while(remaning_size < message->data_size+3){
		tail = (tail + buffer_data[tail]+3)%CAN_BUFFER_SIZE;
		remaning_size = CAN_buffer_remaining_size();
	}
	buffer_data[head] = message->data_size;
	CAN_buffer_increment_head();
	uint8_t adress_array[2] = {0,0};
	convert_from_16_to_8(message->address,adress_array);
	buffer_data[head] = adress_array[0];
	CAN_buffer_increment_head();
	buffer_data[head] = adress_array[1];
	CAN_buffer_increment_head();
	for (int i = 0; i < message->data_size; i++){
		buffer_data[head] = message->data[i];
		CAN_buffer_increment_head();
	}
}



can_message CAN_buffer_read(){
	can_message message;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		message.data_size = buffer_data[tail];
		CAN_buffer_increment_tail();
		
		if(tail < CAN_BUFFER_SIZE-1){
			message.address = convert_from_8_to_16(buffer_data[tail],buffer_data[tail+1]);
			CAN_buffer_increment_tail();
			CAN_buffer_increment_tail();
		}
		else{
			message.address = convert_from_8_to_16(buffer_data[tail], buffer_data[0]);
			CAN_buffer_increment_tail();
			CAN_buffer_increment_tail();
		}
		for(int i = 0; i<message.data_size ; i++){
			message.data[i] = buffer_data[tail];
			CAN_buffer_increment_tail();
		}
	}
	return message;
}

void CAN_buffer_test(){
	can_message message1;
	message1.address = 4;
	message1.data_size = 8;
	for (int i = 0; i < message1.data_size; i++){
		message1.data[i] = i;
	}	
	can_message message2;
	message2.address = 0x2;
	message2.data_size = 5;
	for (int i = 0; i < message2.data_size; i++){
		message2.data[i] = i+10;
	}
	can_message message3;
	message3.address = 0x3;
	message3.data_size = 6;
	for (int i = 0; i < message3.data_size; i++){
		message3.data[i] = i+100;
	}	
	CAN_transmit_message(&message1);
	CAN_transmit_message(&message2);
	CAN_transmit_message(&message3);
}