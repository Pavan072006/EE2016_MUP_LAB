

#ifndef __UART_H 
#define __UART_H

void uart0_init (void);
void uart1_init (void);

char uart0_getc(void);
char uart1_getc(void);

void uart0_putc	(char);
void uart1_putc	(char);

void uart0_puts	(char *);
void uart1_puts	(char *);


#endif

