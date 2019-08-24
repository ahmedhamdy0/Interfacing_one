/*
	Exercise (2) :
	=====================================================================
	Write Embedded C Code Using Atmega16 microcontroller to control a Led
	requirements :
	 - Configure MicroController with the Internal 8 MHz Clock .
	 - LED is connected to Pin6 of PORTD .
	 - Connect the LED using Negative Logic configuration .
	 - Flash the LED every 1 second
*/

#include <avr/io.h>
#include <util/delay.h>

int main( void )
{
	/* Initialization Code */
	DDRD |= (1<<6) ; // D6 LED Output
	PORTD |= (1<<6) ; // LED Off at the Beginning   ( negative logic )

	/* Application Code */
	while(1)
	{
		_delay_ms(1000) ;
		PORTD = PORTD ^(1<<6) ; // toggle led state with xor
		_delay_ms(1000 ) ;
	}
}
