
/*****************************************************************************

DEVELOPED BY:- ARK DEVELOPER
WHAT PROGRAM DO:-This Program read data from PC through UART0 and send back to PC through UART0.

******************************************************************************/

#include "LPC214x.H"              /* LPC214x definitions                     */
#include "uart_poll.h"

#define UART0_TEXT "\n\rUART0 echo back demo...\n\rPress any key and get back... \n\r"

/*****************************************************************************
**   Main Function  main()					
******************************************************************************/
int main (void)
{
	uart0_init();					// Initialize UART0	
	uart0_puts (UART0_TEXT);		// Transffer data to PC through Serial

	while(1)
	{
		uart0_putc(uart0_getc()+3);
	}

//	return 0;
}
/******************************************************************************
**                            End Of File
******************************************************************************/

