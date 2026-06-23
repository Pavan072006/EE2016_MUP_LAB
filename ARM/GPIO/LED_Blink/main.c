
#include "LPC214x.h"                        /* LPC21xx definitions */
#include "led.h"
#include "delay.h"

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
	int i;
	set_led_port_output();
	delay_mSec(10);

	while(1)
	{
			
			for(i=0;i<3;i++)
		{
			Led_On_All();
			delay_mSec(20);
			Led_Off_All();
			delay_mSec(20);
		}

	}
}

