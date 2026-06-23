/*----------------------------------------------------------------------------------
                        ARK-LPC2148 LCD library for 4-bit mode
Filename: lcd_4_bit.c
Controller: LPC2148(ARM7 family)
Oscillator: 12 MHz
Author: Prabhu.S

 ----------------------------------------------------------------------------------
Note:
 1.Pin connection for LCD display in 4-bit mode.
 2.By default the LCD is connected to Port0.
            _______________________________________________
           |                                               |
           |              16*2 lcd  Display                |
           |                4-bit Mode                     |
           |                                               |
           |                                               |
           |                                               |
           |         D7 D6 D5 D4 D3 D2 D1 D0     EN RW RS  |
            -----------------------------------------------
                     |  |  |  |                  |  |  |
                     |  |  |  |					 |	|  |
                     |	|  |  |             	 |  |  |___P0.12
					 |  |  |  | 	             |  |______GND
                     |  |  |  |                  |_________P0.13
					 |	|  |  |
					 |	|  |  |____________________________P0.15
					 |  |  |_______________________________P0.16
					 |  |__________________________________P0.17
					 |_____________________________________P0.18


----------------------------------------------------------------------------------*/
#include <LPC214x.H>                       /* LPC214x definitions */
#include "delay.h"
#include "lcd.h"



/* 16x2 LCD Specification */
#define LCDMaxLines	2
#define LCDMaxChars 16
#define LineOne		0x80
#define LineTwo		0xc0

#define BlankSpace ' '


/*----------------------------------------------------------------------------------
                     void LCD_EnablePulse()
 ----------------------------------------------------------------------------------
 * Function name: LCD_EnablePulse()
 * I/P Arguments: none.
 * Return value	: none
 * description  :This function is used to provide a enable pulse to latch data/command 
 LCD, since it is used frequently making it a function.
----------------------------------------------------------------------------------*/

void LCD_EnablePulse(void)
{
	IO0SET = LCD_EN;	
	IO0CLR = LCD_EN;
}


/*----------------------------------------------------------------------------------
                         void LCD_Init()
 ----------------------------------------------------------------------------------
 * Function name:  LCD_Init()
 * I/P Arguments: none.
 * Return value	: none

 * description  :This function is used to initialize the lcd in 4-bit mode

----------------------------------------------------------------------------------*/
void LCD_Init(void)
{
	set_lcd_port_output();

	delay_mSec(200);

	LCD_CmdWrite(0x20);				// LCD 4-bit interface
	LCD_CmdWrite(0x28);				// LCD 4-bit interface, 2 lines
	LCD_CmdWrite(0x0C);				// display on, cursor off, cursor blink off
	LCD_CmdWrite(0x06);				// increment cursor position, no display shift
	LCD_CmdWrite(0x01);				// Clear display 
	LCD_CmdWrite(0x80);				// Move the Cursor to First line First Position 

}

/**
********************************************************************************************
  Function Name :	set_led_port_output()
  
  Description   :	
  
** parameters:			None
** Returned value:		None
  
  Note          :
********************************************************************************************
*/
void set_lcd_port_output( void )
{
// Enable LCD PINs 
//----------------
//	PINSEL0 = 0x0;									// Pin function Select -> P0.0 to P0.15 -> GPIO Port
//	PINSEL1 = 0x0;									// Pin function Select -> P0.16 to P0.31 -> GPIO Port

	IO0DIR |= (LCD_RS | LCD_EN | LCD_DATA_MASK);	// GPIO Direction control -> pin is output 

	IO0DIR |= LCD_DRIVER_OUTPUT_EN;					// GPIO Direction control -> pin is output 
	IO0CLR |= LCD_DRIVER_OUTPUT_EN;					// GPIO Port Output Clear register -> LCD HARDWARE_DRIVER(74LVC244) ENABLE -> P0.7 goes LOW  


// Disable LED PINs
//-----------------
	IO0DIR |= LED_DRIVER_OUTPUT_EN;					// GPIO Direction control -> pin is output 
	IO0SET |= LED_DRIVER_OUTPUT_EN;					// GPIO Port Output Clear register -> LED HARDWARE_DRIVER(74LVC244) DISABLE -> P0.5 goes HIGH  
}


/*---------------------------------------------------------------------------------
                         void LCD_Clear()
 ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value	: none

 * description  :This function clears the LCD and moves the cursor to first Position

-----------------------------------------------------------------------------------*/
void LCD_Clear(void)
{
   LCD_CmdWrite(0x01);	// Clear the LCD and go to First line First Position
}



void LCD_ClearLineTwo(void)
{
	LCD_GoToLineTwo();
	LCD_DisplayString("                ");		// 16 space 
}

/*---------------------------------------------------------------------------------
                         void LCD_GoToLineOne()
 ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value	: none

 * description  :This function moves the Cursor to First line First Position

-----------------------------------------------------------------------------------*/
void LCD_GoToLineOne(void)
{
   LCD_CmdWrite(LineOne);	// Move the Cursor to First line First Position
}




/*---------------------------------------------------------------------------------
                         void LCD_GoToLineTwo()
 ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value	: none

 * description  :This function moves the Cursor to Second line First Position

-----------------------------------------------------------------------------------*/
void LCD_GoToLineTwo(void)
{
   LCD_CmdWrite(LineTwo);	// Move the Cursor to Second line First Position
}




/*---------------------------------------------------------------------------------
                         void LCD_GoToXY(char row,char col)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char row,char col
                 row -> line number(line1=0, line2=1),
                        For 2line LCD the I/P argument should be either 0 or 1.
                 col -> char number.
                        For 16-char LCD the I/P argument should be betwen 0-15.
 * Return value	: none

 * description  :This function moves the Cursor to specified position

-----------------------------------------------------------------------------------*/
void LCD_GoToXY(char row, char col)
{
	char pos;
	
	if(row<LCDMaxLines)
	{
		pos= LineOne | (row << 6);	// take the line number
									// row0->pos=0x80  row1->pos=0xc0
		
		if(col<LCDMaxChars)
			pos= pos+col;			// take the char number
									// now pos points to the given XY pos
		
		LCD_CmdWrite(pos);			// Move the Cursor specified Position
	}
}

/*----------------------------------------------------------------------------------
                       void LCD_CmdWrite( char cmd)
------------------------------------------------------------------------------------
 * I/P Arguments: 8-bit command supported by LCD.
 * Return value	: none

 * description  :This function sends a command to LCD in the following steps.
     steP0: Send the Higher Nibble of the I/P command to LCD.
     step2: Select the Control Register by making RS low.
     step3: Select Write operation making RW low.
	 step4: Send a High-to-Low pulse on Enable PIN with some delay_us.

	 step5: Send the Lower Nibble of the I/P command to LCD.
	 step6: Select the Control Register by making RS low.
	 step7: Select Write operation making RW low.
	 step8: Send a High-to-Low pulse on Enable PIN with some delay_us.
----------------------------------------------------------------------------------*/
void LCD_CmdWrite( char cmd)
{
	char Lower_Nibble, Higher_Nibble;

	IO0CLR = LCD_RS;						// Select the Command Register by pulling RS LOW
	IO0CLR = LCD_EN;						// Select the Write Operation  by pulling RW LOW
	delay_100uSec();						// wait for some time

	Lower_Nibble =(cmd & 0x0f);
	Higher_Nibble = ((cmd >> 4) & 0x0f);

	IO0PIN &= 0xFFF87FFF;
	IO0PIN |= Higher_Nibble << LCD_DATA_SHIFT;	// Send the Higher Nibble of the command to LCD
	LCD_EnablePulse();

	delay_100uSec();							// wait for some time

	IO0PIN &= 0xFFF87FFF;
	IO0PIN |= Lower_Nibble << LCD_DATA_SHIFT;	// Send the Lower Nibble of the command to LCD
	LCD_EnablePulse();

	delay_mSec(5);
}


/*---------------------------------------------------------------------------------
                       void LCD_DataWrite( char dat)
 ----------------------------------------------------------------------------------
 * Function name: LCD_DataWrite()
 * I/P Arguments: ASCII value of the char to be displayed.
 * Return value	: none

 * description  :
    This function sends a character to be displayed on LCD in the following steps.
       steP0: Send the higher nibble of the character to LCD.
       step2: Select the Data Register by making RS high.
       step3: Select Write operation making RW low.
	   step4: Send a High-to-Low pulse on Enable PIN with some delay_us.

       step5: wait for some time

       step6: Send the lower nibble of the character to LCD.
	   step7: Select the Data Register by making RS high.
	   step8: Select Write operation making RW low.
	   step9: Send a High-to-Low pulse on Enable PIN with some delay_us.
----------------------------------------------------------------------------------*/
void LCD_DataWrite( char dat)
{
	char Lower_Nibble, Higher_Nibble;

	IO0SET = LCD_RS;						// Select the Data Register by pulling RS HIGH
	IO0CLR = LCD_EN;						// Select the Write Operation  by pulling RW LOW
	delay_100uSec();						// wait for some time

	Lower_Nibble =(dat & 0x0f);
	Higher_Nibble = ((dat >> 4) & 0x0f);

	IO0PIN &= 0xFFF87FFF;
	IO0PIN |= Higher_Nibble << LCD_DATA_SHIFT;	// Send the Higher Nibble of the data to LCD
	LCD_EnablePulse();

	delay_100uSec();							// wait for some time

	IO0PIN &= 0xFFF87FFF;
	IO0PIN |= Lower_Nibble << LCD_DATA_SHIFT;	// Send the Lower Nibble of the data to LCD
	LCD_EnablePulse();

	delay_mSec(5);
}


/*---------------------------------------------------------------------------------
                       void LCD_DisplayString(char *string_ptr)
 ----------------------------------------------------------------------------------
 * Function name:  lcd_display_string()
 * I/P Arguments: String(Address of the string) to be displayed.
 * Return value	: none

 * description  :
               This function is used to display the ASCII string on the lcd.
                 1.The string_ptr points to the first char of the string
                    and traverses till the end(NULL CHAR).
                 2.Each time a char is sent to lcd_dat funtion to display.
-----------------------------------------------------------------------------------*/
void LCD_DisplayString(char *string_ptr)
{
	while(*string_ptr)
	LCD_DataWrite(*string_ptr++);
}

/*---------------------------------------------------------------------------------
                      void  LCD_DisplayNumber(unsigned int num)
 ----------------------------------------------------------------------------------
 * Function name:  LCD_DisplayNumber()
 * I/P Arguments: unsigned int.
 * Return value	: none

 * description  :This function is used to display a 5-digit integer(0-65535).
                 ex: if the number is 12345 then 12345 is displayed.
                     if the number is 123 then 00123 is displayed.


 __________Take 1 by dividing by 10000 and add 0X30 to obtain the ASCII value,
|           then take the 4-digit remainder(2345).
|
| _________Take 2 by dividing by 1000  and add 0X30 to obtain the ASCII value,
||           then take the 3-digit remainder(345)
||
|| ________Take 3 by dividing by 100   and add 0X30 to obtain the ASCII value,
|||           then take the 2-digit remainder(45).
|||
||| _______Take 4 by dividing by 10    and add 0X30 to obtain the ASCII value,
|||| ______Take 5 the remainder of 45  and add 0X30 to obtain the ASCII value,.
|||||
12345
-----------------------------------------------------------------------------------*/
void LCD_DisplayNumber(unsigned int num)
{
   LCD_DataWrite((num/10000)+0x30);
   num=num%10000;

   LCD_DataWrite((num/1000)+0x30);
   num=num%1000;

   LCD_DataWrite((num/100)+0x30);
   num=num%100;

   LCD_DataWrite((num/10)+0x30);

   LCD_DataWrite((num%10)+0x30);

 }


/*---------------------------------------------------------------------------------
                  void LCD_ScrollMessage(char *msg_ptr)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char *msg_ptr
                 msg_ptr -> pointer to the string to be scrolled

 * Return value	: none

 * description  :This function scrolls the given message on the first line.
        1.16 chars are displayed at atime.
        2.Pointer is incremented to skip a char each time to give the illusion of
           moving chars
        3.If the chars are less than 16, then the BlankSpaces are displayed.

-----------------------------------------------------------------------------------*/

void LCD_ScrollMessage(char *msg_ptr)
{
	unsigned char i,j;

	for(i=0;msg_ptr[i];i++)			// Loop to display the string complete
	{								// each time 16 chars are displayed and
									// pointer is incremented to point to next char
	
		LCD_CmdWrite(LineOne);		// Move the Cursor to first line
		
		for(j=0;j<LCDMaxChars && msg_ptr[i+j];j++)	// loop to Display first 16 Chars
			LCD_DataWrite(msg_ptr[i+j]);			// or till Null char
		
		for(j=j; j<LCDMaxChars; j++)				// If the chars are below 16
			LCD_DataWrite(BlankSpace);				// then display blank spaces
		
		delay_mSec(300);
	}
}


/*---------------------------------------------------------------------------------
                  LCD_DisplayRtcTime(char hour,char min,char sec)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char hour,char min,char sec
             hour,min,sec should be packed BCD format, as read from DS1307

 * Return value	: none

 * description  :This function display hour,min,sec read from DS1307.

   ___________ Display the higher nibble of hour after adding 0x30(ASCII conversion)
  |            Display the lower nibble of hour after adding 0x30(ASCII conversion)
  |
  |	  ________ Display the higher nibble of min after adding 0x30(ASCII conversion)
  |	 |     	   Display the lower nibble of min after adding 0x30(ASCII conversion)
  |	 |
  |	 |	 _____ Display the higher nibble of sec after adding 0x30(ASCII conversion)
  |	 |	|      Display the lower nibble of sec after adding 0x30(ASCII conversion)
  |	 |	|
  10;40;07

-----------------------------------------------------------------------------------*/
void LCD_DisplayRtcTime(char hour,char min,char sec)
{

	LCD_DataWrite((hour/10)+0x30);		// add 0X30 to obtain the ASCII value,
	LCD_DataWrite((hour%10)+0x30);		// add 0X30 to obtain the ASCII value,
    LCD_DataWrite(':');
	
	LCD_DataWrite((min/10)+0x30);
	LCD_DataWrite((min%10)+0x30);
    LCD_DataWrite(':');
	
	LCD_DataWrite((sec/10)+0x30);
	LCD_DataWrite((sec%10)+0x30);
}



/*---------------------------------------------------------------------------------
                  LCD_DisplayRtcDate(char day,char month,char year)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char day,char month,char year
             day,month,year should be packed BCD format, as read from DS1307

 * Return value	: none

 * description  :This function display day,month,year read from DS1307.

   ___________ Display the higher nibble of day after adding 0x30(ASCII conversion)
  |            Display the lower nibble of day after adding 0x30(ASCII conversion)
  |
  |   ________ Display the higher nibble of month after adding 0x30(ASCII conversion)
  |  |         Display the lower nibble of month after adding 0x30(ASCII conversion)
  |  |
  |  |	 _____ Display the higher nibble of year after adding 0x30(ASCII conversion)
  |  |	|      Display the lower nibble of year after adding 0x30(ASCII conversion)
  |  |	|
  01/01/12 (1st-Jan 2012)

-----------------------------------------------------------------------------------*/
void LCD_DisplayRtcDate(char day,char month, int year)
{
	LCD_DataWrite((day/10)+0x30);		// add 0X30 to obtain the ASCII value,
	LCD_DataWrite((day%10)+0x30);		// add 0X30 to obtain the ASCII value,
    LCD_DataWrite('/');
	
	LCD_DataWrite((month/10)+0x30);
	LCD_DataWrite((month%10)+0x30);
    LCD_DataWrite('/');

	LCD_DataWrite((year/1000)+0x30);
	year=year%1000;
	LCD_DataWrite((year/100)+0x30);
	year=year%100;
	LCD_DataWrite((year/10)+0x30);
	LCD_DataWrite((year%10)+0x30);	
}

