/*
	Exercise ( 1 ) :
	=======================================================================
	write a code to control a LED with Push Button .
	- configure the micro-controller with the internal 1MHz Clock
	- Push Button ... Pin 3 in PortA using Pull Down configuration
	- LED is connected to Pin 5 in PortC using Positive Logic configuration
	- Turn-ON LED when switch is pressed
	- Turn-OFF LED when switch is released
*/


#include <avr/io.h>
int main(void)
{
	/* Initialization */
	DDRA &= ~(1<<3) ;    // Push Button  : A3 Input
	DDRC |= (1<<5) ;     // LED          : C5 Output
	PORTC &= ~(1<<5) ;   // LED - OFF at the beginning
	/* Application Code */
	while(1)
	{
		if(PINA & (1<<3) )
		{
			PORTC |= (1<<5) ; // ON
		}
		else
		{
			PORTC &= ~(1<<5) ; // OFF
		}
	}
}
