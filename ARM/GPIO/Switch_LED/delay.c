/*----------------------------------------------------------------------------------
		ARK-LPC2148 delay library  with the crystal frequency 12MHz
		
Filename: delay.c
Controller: LPC2148(ARM7 family)
Oscillator: 12.0 MHz
Author: Prabhu.S

DATE: 04-03-2016

 ----------------------------------------------------------------------------------*/

#include "delay.h"

/*----------------------------------------------------------------------------------
                         void delay_10uSec(void)
 ----------------------------------------------------------------------------------
 
 * Return value	: none

 * description :
         This function is used generate a approximate delay in 10uSec.

-----------------------------------------------------------------------------------*/

void delay_10uSec(void)		// pr_note:~10 uSec
{
  int j=0,i=0;
 
  for(j=0;j<10;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<50;i++);
  }
}


/*----------------------------------------------------------------------------------
                         void delay_100uSec(void)
 ----------------------------------------------------------------------------------
 
 * Return value	: none

 * description :
         This function is used generate a approximate delay in 100uSec.

-----------------------------------------------------------------------------------*/

void delay_100uSec(void)		// pr_note:~100 uSec
{
  int j=0,i=0;
 
  for(j=0;j<100;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<10;i++);
  }
}


/*----------------------------------------------------------------------------------
                         void delay_mSec(int dCnt)
 -----------------------------------------------------------------------------------
 * I/P Arguments: int
 * Return value	: none

 * description:
     This function is used generate delay in ms.
     It genarates a approximate delay of 1ms for each count,
     if 1000 is passed as the argument then it generates delay of apprx 1000ms(1sec)
-----------------------------------------------------------------------------------*/

void delay_mSec(int dCnt)		// pr_note:~dCnt mSec
{
  int j=0,i=0;

  while(dCnt--) 
  {
	  for(j=0;j<1000;j++)
	  {
	    /* At 60Mhz, the below loop introduces
	    delay of 10 us */
	    for(i=0;i<10;i++);
	  }
  }
}

