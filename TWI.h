#include "HD44780.h"
#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>





#ifndef TWI_H_
#define TWI_H_


void TWI_start(void);
void TWI_repeated_start(void);
void TWI_init_master(void);
void TWI_write_address(unsigned char);
void TWI_read_address(unsigned char);
void TWI_write_data(unsigned char);
char TWI_read_data(void);
void TWI_stop(void);
void TWI_check_ack(unsigned char);
void ERROR(void);



#endif /* TWI_H_ */