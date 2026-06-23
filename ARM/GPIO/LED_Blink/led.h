
#include <LPC214x.H>			/* LPC21xx definitions */

#define BIT(x)	(1 << x)

#define LED_D0	(1 << 10)		// P0.10
#define LED_D1	(1 << 11)		// P0.11
#define LED_D2	(1 << 12)		// P0.12
#define LED_D3	(1 << 13)		// P0.13

#define LED_D4	(1 << 15)		// P0.15
#define LED_D5	(1 << 16)		// P0.16
#define LED_D6	(1 << 17)		// P0.17
#define LED_D7	(1 << 18)		// P0.18

#define LED_IOPIN		IO0PIN
#define LED_CTRL_DIR	IO0DIR
#define LED_CTRL_SET	IO0SET
#define LED_CTRL_CLR	IO0CLR


#define LED_DATA_MASK			((unsigned long)((LED_D7 | LED_D6 | LED_D5 | LED_D4 | LED_D3 | LED_D2 | LED_D1 | LED_D0)))
#define LED_ODD_DATA_MASK		((unsigned int)(LED_D7 | LED_D5 | LED_D3 | LED_D1))
#define LED_EVEN_DATA_MASK		((unsigned int)(LED_D6 | LED_D4 | LED_D2 | LED_D0))

/*----------------------------------------------------------------------------------*/

#define LED1_ON		LED_IOPIN |= (unsigned long)(LED_D0);		// LED1 ON
#define LED2_ON		LED_IOPIN |= (unsigned long)(LED_D1);		// LED2 ON
#define LED3_ON		LED_IOPIN |= (unsigned long)(LED_D2);		// LED3 ON
#define LED4_ON		LED_IOPIN |= (unsigned long)(LED_D3);		// LED4 ON
#define LED5_ON		LED_IOPIN |= (unsigned long)(LED_D4);		// LED5 ON
#define LED6_ON		LED_IOPIN |= (unsigned long)(LED_D5);		// LED6 ON
#define LED7_ON		LED_IOPIN |= (unsigned long)(LED_D6);		// LED7 ON
#define LED8_ON		LED_IOPIN |= (unsigned long)(LED_D7);		// LED8 ON


#define LED1_OFF	LED_IOPIN &= ~(unsigned long)(LED_D0);		// LED1 OFF
#define LED2_OFF	LED_IOPIN &= ~(unsigned long)(LED_D1);		// LED2 OFF
#define LED3_OFF	LED_IOPIN &= ~(unsigned long)(LED_D2);		// LED3 OFF
#define LED4_OFF	LED_IOPIN &= ~(unsigned long)(LED_D3);		// LED4 OFF
#define LED5_OFF	LED_IOPIN &= ~(unsigned long)(LED_D4);		// LED5 OFF
#define LED6_OFF	LED_IOPIN &= ~(unsigned long)(LED_D5);		// LED6 OFF
#define LED7_OFF	LED_IOPIN &= ~(unsigned long)(LED_D6);		// LED7 OFF
#define LED8_OFF	LED_IOPIN &= ~(unsigned long)(LED_D7);		// LED8 OFF

/*----------------------------------------------------------------------------------*/

#ifndef LED_DRIVER_OUTPUT_EN
#define LED_DRIVER_OUTPUT_EN (1 << 5)	// P0.5
#endif

#ifndef LCD_DRIVER_OUTPUT_EN
#define LCD_DRIVER_OUTPUT_EN (1 << 7)	// P0.7
#endif

/*----------------------------------------------------------------------------------*/

void Led_On_All(void);
void Led_Off_All(void);
void Led_Toggle(void);
void Turn_On_Led(int value);
void set_led_port_output( void );
