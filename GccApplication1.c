
#include "HD44780.h"
#include "MPU6050.h"
#include <math.h>
#include "UART.h"
#define F_CPU		16000000 	// czêstotliwoœæ zegara w Hz


void delay_ms( int ms)
{
	volatile long unsigned int i;
	for(i=0;i<ms;i++)
	_delay_ms(1);
}


int main(){
	USART_Init(51);

	char buf[17]="                ";
	DDRD = 0x00;
	char tab =0x00;
	float x;
	float y;
	int d1;
	int d2;
	PORTD = 0xff;
	TWBR = 200;
	
	LCD_Initalize();
	LCD_Clear();
	Setup_MPU6050(MPU_1_ADRESS);

	while(1){
		LCD_Clear();
		if((PIND & 0x1) == 0){
			LCD_Clear();
		}
		if((PIND & 0x2) == 0){
			tab |= 0x01;			
		}
		if((PIND & 0x4) == 0){
			
		}
		if(tab==0x0f){
	
		}
		tab=tab<<1;
		Get_Accel_Values(MPU_1_ADRESS);
		x=(float)ACCEL_ZOUT/16384;
		x*=2*9.81;
		d1 = x;
		y = x-d1;
		d2 = trunc(y * 10000); 
		//sprintf(buf,"XAcc:  %d",ACCEL_ZOUT);
		sprintf(buf,"ZAcc:  %d.%04d",d1,abs(d2));
		LCD_WriteText(buf);
		USART_Transmit('a');
		_delay_ms(1000);
	}
	return 0;
}