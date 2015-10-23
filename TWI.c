#include "TWI.h"

void TWI_check_status(char code)
{
	if((TWSR & 0xF8)!= code)
	ERROR(); // Check for the acknowledgement
}

void TWI_operation()
{
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
}


void TWI_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
	TWI_check_status(0x08);
	
}

void TWI_repeated_start(void){
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // wait till restart condition is transmitted
	TWI_check_status(0x10);
}

void TWI_read_address(unsigned char data)
{
	TWDR=data;  // Address and read instruction
	TWI_operation();
	TWI_check_status(0x40);
}

void TWI_write_data(unsigned char data)
{
	TWDR=data;  // put data in TWDR
	TWI_operation();
	TWI_check_status(0x28);
}

 char TWI_read_data(void)
{
	TWI_operation();
	TWI_check_status(0x58);
	//while((TWSR & 0xF8) != 0x58); // Check for the acknowledgement
	char data = TWDR;
	return data;
}

void TWI_stop(void)
{
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	_delay_us(100);
}

void TWI_check_ack(unsigned char adress){
	TWDR = adress;
	TWI_operation();
	TWI_check_status(0x18);
}

void ERROR()
{
	char buf[17]="                ";
	LCD_Clear();
	int x=TWSR;
	sprintf(buf,"Comm Err: %02x",x);
	LCD_WriteText(buf);
	delay_ms(1000);
	LCD_Clear();
}