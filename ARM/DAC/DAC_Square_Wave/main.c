
//DAC program to generate a square wave 
//Amplitude  0 to 1374mV  (Oscilloscope  reads 1420mV)
//Frequency 500Hz         (oscilloscope  reads  434.0 Hz)

#include "LPC214x.H"     /* LPC214x definitions */
#include "delay.h"

#define DAC_BIAS			0x00010000

#define DAC_FullScale_CountValue	1024	// 2^10 - 10 bit DAC 
#define DAC_FullScale_mVolt	3300	// 3.3V - DAC Reference Voltage

#define DAC_OUT_mVolt		2500	// 2.5V


void DACInit( void )
{
   
	PINSEL1 &= 0xFFF3FFFF; // /* setup the related pin to DAC output */
    PINSEL1 |= 0x00080000;	/* set p0.25 to DAC output */   
    return;
}


int main(void)
{
	unsigned long DAC_CountValue;

	DACInit();

//	DAC_CountValue = DAC_OUT_mVolt * ( DAC_FullScale_CountValue / DAC_FullScale_mVolt );	// Find DAC_OUT countvalue
	
	
	while(1)
	{
		DAC_CountValue=0;

	DACR = (DAC_CountValue << 6) | DAC_BIAS;
		delay_mSec(1);
    DAC_CountValue=0x1AA;
	DACR = (DAC_CountValue << 6) | DAC_BIAS;
				delay_mSec(1);
	}
    return 0;
}



