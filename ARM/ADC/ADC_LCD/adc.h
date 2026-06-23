
/*****************************************************************************
 *   adc.h:  Header file for Philips LPC214x Family Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/

#ifndef __ADC_H 
#define __ADC_H


#define CHANNEL_0   0
#define CHANNEL_1   1
#define CHANNEL_2   2
#define CHANNEL_3   3
#define CHANNEL_4   4
#define CHANNEL_5   5
#define CHANNEL_6   6
#define CHANNEL_7   7


/* Crystal frequence,10MHz~25MHz should be the same as actual status. */
#define Fosc		12000000
#define ADC_CLK		1000000		/* set to 1Mhz */

/* A/D Converter 0 (AD0) */
#define AD0_BASE_ADDR		0xE0034000
#define ADC_INDEX			4

#define ADC_DONE			0x80000000
#define ADC_OVERRUN			0x40000000


#define ADC_FullScale_Volt	3.3		// 3.3V - ADC Referance Voltage
#define ADC_FullScale_Count	1024	// 2^10 - 10 bit ADC 


void Init_ADC0(unsigned char channelNum);
unsigned long Read_ADC0( unsigned char channelNum );


#endif
