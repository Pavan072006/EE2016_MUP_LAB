

/*****************************************************************************
 *   adc.c:  ADC module file for Philips LPC214x Family Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/

#include "LPC214x.H"                       /* LPC214x definitions */
#include "adc.h"

/*****************************************************************************
** Function name:		Init_ADC0
**
** Descriptions:		initialize ADC channel
**
** parameters:			Channel number
** Returned value:		
** 
*****************************************************************************/
	
void Init_ADC0(unsigned char channelNum)
{
	if(channelNum == CHANNEL_1)
		PINSEL1 = (PINSEL1 & ~(3 << 24)) | (1 << 24);		// P0.28 -> AD0.1

	if(channelNum == CHANNEL_2)
		PINSEL1 = (PINSEL1 & ~(3 << 26)) | (1 << 26);		// P0.29 -> AD0.2

	if(channelNum == CHANNEL_3)
		PINSEL1 = (PINSEL1 & ~(3 << 28)) | (1 << 28);		// P0.30 -> AD0.3


    AD0CR = ( 0x01 << 1 ) | 					// SEL=1, select channel 0, 1 to 4 on ADC0
			(( Fosc / ADC_CLK - 1 ) << 8 ) |	// CLKDIV = Fpclk / 1000000 - 1 
			( 0 << 16 ) | 						// BURST = 0, no BURST, software controlled
			( 0 << 17 ) |  						// CLKS = 0, 11 clocks/10 bits 
			( 1 << 21 ) |  						// PDN = 1, normal operation 
			( 0 << 22 ) |  						// TEST1:0 = 00 
			( 0 << 24 ) |  						// START = 0 A/D conversion stops
			( 0 << 27 );						/* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */
}


/*****************************************************************************
** Function name:		Read_ADC0
**
** Descriptions:		Read ADC0 channel
**
** parameters:			Channel number
** Returned value:		ADC_Data
** 
*****************************************************************************/
unsigned long Read_ADC0( unsigned char channelNum )
{
    unsigned long regVal, ADC_Data;

	/* Clear all SEL bits */
    AD0CR &= 0xFFFFFF00;
	/* switch channel, start A/D convert */
    AD0CR |= (1 << 24) | (1 << channelNum);	
				

    /* wait until end of A/D convert */
	while ( 1 )	{		
		
//		regVal = *(volatile unsigned long *)(AD0_BASE_ADDR + ADC_INDEX);
		regVal = AD0GDR;

		if ( regVal & ADC_DONE ){
	    	break;
		}
    }	
    
	/* stop ADC now */    
    AD0CR &= 0xF8FFFFFF;
	/* save data when it's not overru otherwise, return zero */	    
    if ( regVal & ADC_OVERRUN )	{
		return ( 0 );
    }
    ADC_Data = ( regVal >> 6 ) & 0x3FF;
    /* return A/D conversion value */
	return ( ADC_Data );	

}

