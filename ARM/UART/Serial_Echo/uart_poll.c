
#include "LPC214x.H"                     /* LPC21xx definitions               */
#include <stdio.h>
#include "uart_poll.h"

#define	CR	0x0D

//------------------------------------------------------------------------------------------------//

///* implementation of putchar (also used by printf function to output data)    */
//int sendchar (int ch)  {                 /* Write character to Serial Port    */
//
//  if (ch == '\n')  {
//    while (!(U1LSR & 0x20));
//    U1THR = CR;                          /* output CR */
//  }
//  while (!(U1LSR & 0x20));
//  return (U1THR = ch);
//}

/* implementation of fputc (also used by printf function to output data)      */
int fputc (int ch, FILE *f)  {           /* Write character to Serial Port    */

  if (ch == '\n')  {
    while (!(U0LSR & 0x20));
    U0THR = CR;                          /* output CR */
  }
  while (!(U0LSR & 0x20));
  return (U0THR = ch);
}

//------------------------------------------------------------------------------------------------//

char uart0_getc (void)  {                     /* Read character from Serial Port   */

  while (!(U0LSR & 0x01));

  return (U0RBR);
}

char uart1_getc (void)  {                     /* Read character from Serial Port   */

  while (!(U1LSR & 0x01));

  return (U1RBR);
}

//------------------------------------------------------------------------------------------------//
//---------------------------- Function for Initial UART1 ----------------------------------------//
//------------------------------------------------------------------------------------------------//

void uart1_init(void)
{
  /* initialize the serial interface   */
  PINSEL0 &= 0xfff0ffff;
  PINSEL0 |= 0x00050000;          /* Enable RxD1 and TxD1                     */
  U1LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
  U1DLL = 97;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
  U1LCR = 0x03;                   /* DLAB = 0                                 */
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send character 1 time via UART1-----------------------//
//------------------------------------------------------------------------------------------------//
void uart1_putc(char c)
{
	while(!(U1LSR & 0x20)); // Wait until UART1 ready to send character     
	U1THR = c;  // Send character
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send string via UART1---------------------------------//
//------------------------------------------------------------------------------------------------//
void uart1_puts(char *p)
{
	while(*p) // Point to character
	{
		uart1_putc(*p++);   // Send character then point to next character
	}
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for Initial UART0 ----------------------------------------//
//------------------------------------------------------------------------------------------------//
void uart0_init(void)
{
  /* initialize the serial interface   */
  PINSEL0 &= 0xfffffff0;
  PINSEL0 |= 0x00000005;          /* Enable RxD0 and TxD0                     */
  U0LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
  U0DLL = 97;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
  U0LCR = 0x03;                   /* DLAB = 0                                 */
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send character 1 time via UART0-----------------------//
//------------------------------------------------------------------------------------------------//
void uart0_putc(char c)
{
	while(!(U0LSR & 0x20)); // Wait until UART0 ready to send character  
	U0THR = c; // Send character
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send string via UART1---------------------------------//
//------------------------------------------------------------------------------------------------//
void uart0_puts(char *p)
{
	while(*p) // Point to character
	{
		uart0_putc(*p++);  // Send character then point to next character
	}
}
//------------------------------------------------------------------------------------------------//

