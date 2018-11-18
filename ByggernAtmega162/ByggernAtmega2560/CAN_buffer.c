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
bool buffer_full;
bool buffer_empty;

void CAN_buffer_init(){
	head = 0;
	tail = head;
	buffer_full = false;
	buffer_empty = true;
	for(int i = 0; i<CAN_BUFFER_SIZE; i++){
		buffer_data[i] = 0;
	}
	
}

void CAN_buffer_increment_head(){
	head = (head + 1) % CAN_BUFFER_SIZE;
	if(head == tail){
		buffer_full = true;
	}
	else{
		buffer_empty = false;
	}
}

void CAN_buffer_increment_tail(){
	tail = (tail + 1) % CAN_BUFFER_SIZE;
	if(tail == head){
		buffer_empty = true;
	}
}
bool CAN_buffer_full(){
	return buffer_full;
}

void CAN_buffer_set_full(){
	buffer_full = true;
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


void CAN_buffer_reset(){
	head = 0;
	tail = 0;
	buffer_full = false;
	buffer_empty = true;
}


void CAN_buffer_write(can_message *message){
	uint8_t remaning_size = CAN_buffer_remaining_size();
	while(remaning_size < message->data_size+3){
		//printf("Deleted message\n\r");
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
		/*if(buffer_full){
			buffer_full = false;
			CAN_interrupt_routine();
			
		}*/
	}
	return message;
}








void CAN_buffer_test(){
	/*can_message message1;
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
	}*/
	
}

void CAN_buffer_test_2(){
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
	//printf("Remaning buffer size test funk: %d\n\n\r", CAN_buffer_remaining_size());
	CAN_transmit_message(&message2);
	//printf("Remaning buffer size test funk: %d\n\n\r", CAN_buffer_remaining_size());
	CAN_transmit_message(&message3);
	//printf("Remaning buffer size test funk: %d\n\n\r", CAN_buffer_remaining_size());
	//printf("Remaining buffer space:	%d\n\r", CAN_buffer_remaining_size());
	//CAN_interrupt_routine();
	//_delay_ms(100);
	//CAN_interrupt_routine();
	//CAN_transmit_message(&message1);
	//CAN_interrupt_routine();
	
	//printf("Remaining buffer space:	%d\n\r", CAN_buffer_remaining_size());
	//CAN_transmit_message(&message2);
	//printf("Remaining buffer space:	%d\n\r", CAN_buffer_remaining_size());
	//_delay_ms(100);
	//CAN_transmit_message(&message2);
	
	
	
	/*can_message r_2;
	r_2.address = 1;
	r_2.data_size = 0;
	for (int i = 0; i<8;i++){
		r_2.data[i] = 0;
	}*/
	//printf("HEi");
	/*printf("Can buffer empty: %i \n\r", CAN_buffer_is_empty());
	while(!CAN_buffer_is_empty()){
		printf("Remaining buffer space:	%d", CAN_buffer_remaining_size());
		r_2 = CAN_buffer_read();
		printf("Remaining buffer space:	%d", CAN_buffer_remaining_size());
		printf("Sendt address: %x	Recieved ardess: %x \n\r",message1.address,r_2.address);
		printf("Sendt data_size: %d	Recieved size: %d \n\r",message1.data_size,r_2.data_size);
		for(int i = 0; i<r_2.data_size; i++){
			printf("Sendt data: %d	Recieved data: %d \n\r",message1.data[i],r_2.data[i]);
		}
	}*/
	//printf("Done");	
}