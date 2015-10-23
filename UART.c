/*
 * UART.c
 *
 * Created: 2015-10-23 09:00:14
 *  Author: Igor
 */ 
#include "UART.h"

void USART_Init(unsigned int baud){
	UBRR0H=(unsigned char) (baud>>8);
	UBRR0L=(unsigned char) baud;
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
	UCSR0C=(1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data){
	while(!(UCSR0A& (1<<UDRE0)));
	UDR0=data;
}