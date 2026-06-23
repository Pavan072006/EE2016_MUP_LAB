
/*****************************************************************************

DEVELOPED BY:- ARK DEVELOPER
WHAT PROGRAM DO:-This Program Read LPC2148 ADC data from ADC0_CH1 & OUT through DAC.

******************************************************************************/

#include "LPC214x.H"                       /* LPC214x definitions */
#include "delay.h"
#include "adc.h"


#define DAC_BIAS	0x00010000

/*****************************************************************************
** Function name:		DACInit
**
** Descriptions:		initialize DAC channel
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void DACInit( void )
{
    /* setup the related pin to DAC output */
	PINSEL1 &= 0xFFF3FFFF;
    PINSEL1 |= 0x00080000;	/* set p0.25 to DAC output */   
    return;
}


/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
	unsigned long ADC_Cnt;

	Init_ADC0(CHANNEL_1);

	DACInit();

	delay_mSec(100);

	while(1)
	{
		ADC_Cnt = Read_ADC0(CHANNEL_1);		// Read from ADC
		DACR = (ADC_Cnt << 6) | DAC_BIAS;	// OUT through DAC
		delay_mSec(100);
	}

//    return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/


