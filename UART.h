/*
 * UART.h
 *
 * Created: 2015-10-23 08:59:38
 *  Author: Igor
 */ 


#ifndef UART_H_
#define UART_H_
#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>
void USART_Init(unsigned int);
void USART_Transmit(unsigned char);



#endif /* UART_H_ */