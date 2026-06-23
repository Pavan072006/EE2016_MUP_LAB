#ifndef _LCD_H
#define _LCD_H


#define P0_12	(1 << 12)
#define P0_13	(1 << 13)

#define P0_15	(1 << 15)
#define P0_16	(1 << 16)
#define P0_17	(1 << 17)
#define P0_18	(1 << 18)

#define LCD_RS	P0_12
#define LCD_EN	P0_13

#define LCD_D4	P0_15
#define LCD_D5	P0_16
#define LCD_D6	P0_17
#define LCD_D7	P0_18

#define LCD_DATA_MASK	(LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)	
#define LCD_DATA_SHIFT	15

//#define LED_LATCH	P0_5
//#define LCD_LATCH	P0_7

#ifndef LED_DRIVER_OUTPUT_EN
#define LED_DRIVER_OUTPUT_EN (1 << 5)	// P0.5
#endif

#ifndef LCD_DRIVER_OUTPUT_EN
#define LCD_DRIVER_OUTPUT_EN (1 << 7)	// P0.7
#endif

/*----------------------------------------------------------------------------------*/

void set_lcd_port_output( void );

void LCD_Init(void);
void LCD_EnablePulse(void);
void LCD_CmdWrite(char);
void LCD_DataWrite(char);
void LCD_Clear(void);										
void LCD_GoToLineOne(void);
void LCD_GoToLineTwo(void);
void LCD_GoToXY(char, char);
void LCD_DisplayString(char *);
void LCD_ScrollMessage(char *);
void LCD_DisplayNumber(unsigned int);
void LCD_DisplayRtcTime(char, char, char);
void LCD_DisplayRtcDate(char, char, int);

void LCD_ClearLineTwo(void);

#endif

