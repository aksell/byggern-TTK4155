/*
 * interrupts.c
 *
 * Created: 26.09.2018 13:39:03
 *  Author: EdvardOlaf
 */ 
#include "interrupts.h"

void interrupt_init() {
	
	DDRD &= ~(1<<PD2);		// Set port D pin 2
	cli();
	 
	
	
	GICR |= 1<<INT0;					// Enable INT0
	//GICR |= 1<<INT1;					// Enable INT1
	MCUCR |= 1<<ISC01; //| 1<<ISC00;	// Trigger INT0 on falling edge
	//MCUCR |= 1<<ISC11 | 0<<ISC10;	// Trigger INT1 on rising edge
	
	sei();
}

ISR(INT0_vect)
{	
	/*if(!CAN_buffer_full()){
		printf("Buffer written from int\n\r");
		can_message message;
		CAN_recive_message(&message);
		
		
		if(CAN_buffer_remaining_size() >= message.data_size + 3){//enough to write the entire message to the buffer
			CAN_buffer_write(&message);
			MCP2515_bit_modify(MCP_CANINTF,(1<<0),1);
		}
		else{
			printf("Buffer set full\n\r");
			CAN_buffer_set_full();
		}
	}
	else{
		printf("Buffer full\n\r");
	}*/
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		printf("Message\n\r");
		CAN_interrupt_routine();
	}
	/*can_message message;
	printf("Address:	%d\n\r",message.address);
	printf("Received data\n\r");
	CAN_recive_message(&message);
	for(int i = 0; i<message.data_size;i++){
		printf("%d\n\r",message.data[i]);
	}
	printf("\n\r");*/
	
	
}


ISR(USART0_RXC_vect)
{
	uart_buffer_write(uart_recive());
}
