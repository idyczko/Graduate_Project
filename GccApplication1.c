#include <math.h>
#include <stdio.h>
#include "HD44780.h"
#include "MPU6050.h"
#include "KALMAN.h"
#include "UART.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define G_ACC 9.81
#define SCALE 16384
#define ACC_SET 0x18 
#define PI 3.14
#define AVER 1000
#define INTRO 100
#define BUTTON_1 ((PIND & 0x1) == 0)
#define BUTTON_2 ((PIND & 0x2) == 0)
#define BUTTON_3 ((PIND & 0x4) == 0)
#define BUTTON_4 ((PIND & 0x8) == 0)
#define BUTTON_5 ((PIND & 0x10) == 0)

int Button_1(){
	static int tick=0;
	if(BUTTON_1){
		tick++;
	}
	if(tick > 5){
		tick = 0;
		return 1;
	}
	return 0;
}

int Button_2(){
	static int tick=0;
	if(BUTTON_2){
		tick++;
	}
	if(tick > 5){
		tick = 0;
		return 1;
	}
	return 0;
}

int Button_3(){
	static int tick=0;
	if(BUTTON_3){
		tick++;
	}
	if(tick > 5){
		tick = 0;
		return 1;
	}
	return 0;
}

int Button_4(){
	static int tick=0;
	if(BUTTON_4){
		tick++;
	}
	if(tick > 5){
		tick = 0;
		return 1;
	}
	return 0;
}

int Button_5(){
	static int tick=0;
	if(BUTTON_5){
		tick++;
	}
	if(tick > 5){
		tick = 0;
		return 1;
	}
	return 0;
}

void delay_ms( int ms)
{
	volatile long unsigned int i;
	for(i=0;i<ms;i++)
	_delay_ms(1);
}


void PrintFloatToLCD(float x, char * message)
{
	char buf[17]="                ";
	strcpy(buf, message);
	strcat(buf, " %d.%04d");
	float y;
	int d1;
	int d2;
	d1 = x;
	y = x-d1;
	d2 = trunc(y * 10000);
	sprintf(buf, buf,d1,abs(d2));
	LCD_WriteText(buf);
}

float Get_Z_Acceleration(unsigned char MPU_ADRESS, float vectorScale, int scale, float offset, kalman_state *kalman)
{
		float x;
		Get_Accel_Values(MPU_ADRESS);
		x=(float)ACCEL_ZOUT/SCALE;
		x*=vectorScale*scale*G_ACC;
		x-=offset;
		kalman_update(&kalman,x);
		PrintFloatToLCD(0.123, "ZAccG");
		return x;
}



int main(){

	DDRD = 0x00;
	PORTD = 0xff;
	TWBR = 100;
	
	char buf[17]="                ";
	char tab =0x00;
	char chosen = 'a';
	int measurementScaleTab[4]={2,4,8,16};
	int measurementScale = measurementScaleTab[ACC_SET>>3];
	float zVectorScale_1;
	float zOffset_1;
	float x;
	int d1=0;
	int d2=0;
	float y;
	
	LCD_Initalize();
	LCD_Clear();
	LCD_WriteText("Initializing...");
	kalman_state kalman = kalman_init(0.1, 1, 1, 0);
	USART_Init(51);
	_delay_ms(INTRO);
	LCD_Clear();
	LCD_WriteText("Calibrating...");
	Setup_MPU6050(MPU_1_ADRESS, ACC_SET);
	Get_Accel_Values(MPU_1_ADRESS);
	_delay_ms(INTRO);
	LCD_Clear();
	zVectorScale_1 =(float) cos(PI/2* MAX(abs(ACCEL_XOUT), abs(ACCEL_YOUT))/SCALE);
	PrintFloatToLCD(zVectorScale_1, "Vector:");
	_delay_ms(INTRO);
	LCD_Clear();
	sprintf(buf,"ZAcc:  %d",ACCEL_ZOUT);
	LCD_WriteText(buf);
	_delay_ms(INTRO);
	LCD_Clear();
	float z=0;
	float t=0;
	for(y=1;y<=AVER;y++){
		Get_Accel_Values(MPU_1_ADRESS);
		t=(float) ACCEL_ZOUT;
		z=((y-1)/y)*z+(1/y)*t;
	}
	zOffset_1=(int) z;
	sprintf(buf,"Offset:  %d",z);
	LCD_WriteText(buf);
	_delay_ms(INTRO);
	LCD_Clear();
	LCD_WriteText("Ready!");
	_delay_ms(INTRO);
	LCD_Clear();

	while(1){
		LCD_Clear();
		if(Button_1()){
			LCD_Clear();
		}
		if(Button_2() && chosen<'c'){	
			chosen++;		
		}
		if(Button_3() && chosen >'a'){
			chosen--;
		}

		//x = Get_Z_Acceleration(MPU_1_ADRESS, zVectorScale_1, measurementScale, zOffset_1, &kalman);
		switch(chosen){
			case 'a':
				Get_Accel_Values(MPU_1_ADRESS);
				x=(float)(ACCEL_ZOUT-zOffset_1)/SCALE;
				x*=zVectorScale_1*measurementScale*G_ACC;
				kalman_update(&kalman,x);
				d1 = kalman.x;
				y = kalman.x-d1;
				d2 = trunc(y * 10000);
				sprintf(buf, "Z_KAL: %d.%04d",d1,abs(d2));
				LCD_WriteText(buf);
				d1 =x;
				y = x-d1;
				d2 = trunc(y * 10000);
				LCD_GoTo(0,1);
				sprintf(buf, "Z_CAL: %d.%04d",d1,abs(d2));
				LCD_WriteText(buf);
				break;
			case 'b':
				Get_Accel_Values(MPU_1_ADRESS);
				sprintf(buf,"X_RAW:  %d",ACCEL_XOUT);
				LCD_WriteText(buf);
				break;
			case 'c':
				Get_Accel_Values(MPU_1_ADRESS);
				sprintf(buf,"Y_RAW:  %d",ACCEL_YOUT);
				LCD_WriteText(buf);
				break;
			default:
				break;
		}
		//PrintFloatToLCD(x, "ZAccG");
		
		//sprintf(buf,"ZAcc:  %d",ACCEL_ZOUT);	
		//LCD_WriteText(buf);
		//USART_Transmit_fl(x);
		//USART_Transmit('.');
		//USART_Transmit(d2);
		_delay_ms(50);
	}
	return 0;
}