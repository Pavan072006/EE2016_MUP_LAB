
#include <LPC214x.H>                        /* LPC21xx definitions */
#include "led.h"

int led_counter;


/**
********************************************************************************************
  Function Name :	set_led_port_output()
  
  Description   :	
  
** parameters:			None
** Returned value:		None
  
  Note          :
********************************************************************************************
*/
void set_led_port_output( void )
{
// Enable LED PINs 
	IO0DIR |= LED_DATA_MASK;			// GPIO Direction control -> pin is output 
	IO0DIR |= LED_DRIVER_OUTPUT_EN;		// GPIO Direction control -> pin is output 
	IO0CLR |= LED_DRIVER_OUTPUT_EN;		// GPIO Port Output Clear register -> LED HARDWARE_DRIVER(74LVC244) ENABLE -> P0.5 goes LOW  

// Disable LCD PINs
	IO0DIR |= LCD_DRIVER_OUTPUT_EN;		// GPIO Direction control -> pin is output 
	IO0SET |= LCD_DRIVER_OUTPUT_EN;		// GPIO Port Output Clear register -> LCD HARDWARE_DRIVER(74LVC244) DISABLE -> P0.7 goes HIGH  
}

//------------------------------------------------------------------------------------

void Led_On_All(void)
{
	LED_IOPIN |= LED_DATA_MASK; 
}

void Led_Off_All(void)
{
	LED_IOPIN &= ~(LED_DATA_MASK); 
}

//------------------------------------------------------------------------------------

void Led_Toggle(void)
{
	led_counter++;

	if( led_counter & 0x01 )	/* alternate the LED display */
	{
		LED_IOPIN &= ~(LED_ODD_DATA_MASK);		 
		LED_IOPIN |= LED_EVEN_DATA_MASK;
	}
	else
	{
		LED_IOPIN &= ~(LED_EVEN_DATA_MASK); 
		LED_IOPIN |= LED_ODD_DATA_MASK;				 
	}
}

//------------------------------------------------------------------------------------

void Turn_On_Led(int value)
{
/*
	int Lower_Nibble, Higher_Nibble;

	Lower_Nibble = (value & 0x0f);
	Higher_Nibble = ((value >> 4) & 0x0f);

	LED_IOPIN &= ~(LED_DATA_MASK);
	LED_IOPIN |= Higher_Nibble << 15;
	LED_IOPIN |= Lower_Nibble  << 10;
*/

	Led_Off_All();

	if(value & BIT(0)) LED8_ON;
	if(value & BIT(1)) LED7_ON;
	if(value & BIT(2)) LED6_ON;
	if(value & BIT(3)) LED5_ON;

	if(value & BIT(4)) LED4_ON;
	if(value & BIT(5)) LED3_ON;
	if(value & BIT(6)) LED2_ON;
	if(value & BIT(7)) LED1_ON;

}

//------------------------------------------------------------------------------------


