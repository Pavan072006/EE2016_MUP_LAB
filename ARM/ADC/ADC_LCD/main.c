

#include <LPC214x.H>                       /* LPC214x definitions */
#include <stdio.h>
#include "delay.h"

#include "adc.h"
#include "lcd.h"

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
	char StrBuf[16];
	unsigned long ADC_Cnt;

	Init_ADC0(CHANNEL_1);
	Init_ADC0(CHANNEL_2);

	delay_mSec(100);

	LCD_Init();

	while(1)
	{
		ADC_Cnt = Read_ADC0(CHANNEL_1);		
		sprintf (StrBuf, "ADC0_CH1 : %04d", ADC_Cnt);
		LCD_GoToLineOne();
		LCD_DisplayString(StrBuf);


		ADC_Cnt = Read_ADC0(CHANNEL_2);
		sprintf (StrBuf, "ADC0_CH2 : %04d", ADC_Cnt);
		LCD_GoToLineTwo();
		LCD_DisplayString(StrBuf);

		delay_mSec(500);
	}

//    return 0;
}




