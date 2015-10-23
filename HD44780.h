#define F_CPU		16000000 	// czêstotliwoœæ zegara w Hz

#include <avr/io.h>
#include <util/delay.h>

//-------------------------------------------------------------------------------------------------
//
// Konfiguracja sygna³ów steruj¹cych wyœwietlaczem.
// Mo¿na zmieniæ stosownie do potrzeb.
//
//-------------------------------------------------------------------------------------------------
#define WAITFORTIMER()  { while ( timerflag == 0); timerflag = 0; }
#define TIMER_2_CNT 0x22     //  111us with CLK/8 prescale kwarc 16mhz 0x22 /4mhz 0xc9
#define F_OSC 16000000UL

#define LCD_RW_DIR		DDRC
#define LCD_RW_PORT		PORTC
#define LCD_RW_PIN		PINC
#define LCD_RW			(1 << PC3)

#define LCD_RS_DIR		DDRB
#define LCD_RS_PORT 	PORTB
#define LCD_RS_PIN		PINB
#define LCD_RS			(1 << PB1)

#define LCD_E_DIR		DDRB
#define LCD_E_PORT		PORTB
#define LCD_E_PIN		PINB
#define LCD_E			(1 << PB0)

#define LCD_DB4_DIR		DDRC
#define LCD_DB4_PORT	PORTC
#define LCD_DB4_PIN		PINC
#define LCD_DB4			(1 << PC4)

#define LCD_DB5_DIR		DDRC
#define LCD_DB5_PORT	PORTC
#define LCD_DB5_PIN		PINC
#define LCD_DB5			(1 << PC5)

#define LCD_DB6_DIR		DDRC
#define LCD_DB6_PORT	PORTC
#define LCD_DB6_PIN		PINC
#define LCD_DB6			(1 << PC6)

#define LCD_DB7_DIR		DDRC
#define LCD_DB7_PORT	PORTC
#define LCD_DB7_PIN		PINC
#define LCD_DB7			(1 << PC7)


//-------------------------------------------------------------------------------------------------
//
// Instrukcje kontrolera Hitachi HD44780
//
//-------------------------------------------------------------------------------------------------

#define HD44780_CLEAR					0x01

#define HD44780_HOME					0x02

#define HD44780_ENTRY_MODE				0x04
#define HD44780_EM_SHIFT_CURSOR		0
#define HD44780_EM_SHIFT_DISPLAY	1
#define HD44780_EM_DECREMENT		0
#define HD44780_EM_INCREMENT		2

#define HD44780_DISPLAY_ONOFF			0x08
#define HD44780_DISPLAY_OFF			0
#define HD44780_DISPLAY_ON			4
#define HD44780_CURSOR_OFF			0
#define HD44780_CURSOR_ON			2
#define HD44780_CURSOR_NOBLINK		0
#define HD44780_CURSOR_BLINK		1

#define HD44780_DISPLAY_CURSOR_SHIFT	0x10
#define HD44780_SHIFT_CURSOR		0
#define HD44780_SHIFT_DISPLAY		8
#define HD44780_SHIFT_LEFT			0
#define HD44780_SHIFT_RIGHT			4

#define HD44780_FUNCTION_SET			0x20
#define HD44780_FONT5x7				0
#define HD44780_FONT5x10			4
#define HD44780_ONE_LINE			0
#define HD44780_TWO_LINE			8
#define HD44780_4_BIT				0
#define HD44780_8_BIT				16

#define HD44780_CGRAM_SET				0x40

#define HD44780_DDRAM_SET				0x80

//-------------------------------------------------------------------------------------------------
//
// Deklaracje funkcji
//
//-------------------------------------------------------------------------------------------------

void LCD_WriteCommand(unsigned char);
unsigned char LCD_ReadStatus(void);
void LCD_WriteData(unsigned char);
unsigned char LCD_ReadData(void);
void LCD_WriteText(char *);
void LCD_GoTo(unsigned char, unsigned char);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_Initalize(void);

//-------------------------------------------------------------------------------------------------
//
// Koniec pliku HD44780.h
//
//---------------------------------------------------------------