/*
	Exercise 3 :
	==========================================================
	write embedded c code using atmega16 to control two leds using two push buttons
	requirements :
		- Configure Micro Controller With the internal 1Mhz Clock .
		- switches 1 and 2 are connected to Pin0 and Pin1 in PortB .
		- Connect both switches using Pull Down configuration .
		- LEDs 1 and 2 are connected to Pin0 , Pin1 of PortC .
		- connect two leds using positive logic configuration .
		- if switch one is pressed just Turn-ON the First LED Only , and if switch 2 is pressed
		  just Turn-ON LED 2 Only .
		- In Case both switches are pressed .. Both LEDs are ON .
		- In Case no switches are pressed  .. Both LEDs are OFF .
*/

#include <avr/io.h>
int main()
{
	/* Initialization Code */
	DDRB &= ~(1<<0) ;  // B0 input (switch 1)
   	DDRB &= ~(1<<1) ;  // B1 input (switch 2)
	DDRC |= (1<<0) | (1<<1) ; // C0 (First LED) , C1 (Second LED )  Outputs
	PORTC &= ~( 1<<0) ;   // First LED OFF
	PORTC &= ~(1<<1) ; // Second LED OFF

	/* Application Code */
	while(1)
	{
		//  check first switch
		if(PINB &(1<<0) )
		{
			PORTC |= (1<<0) ; // LED ONE ONE
		}
		else{
			PORTC &= ~(1<<0) ; // LED ONE OFF
		}
		//-----------------------
		// check second switch
		if( PINB &(1<<1) )
		{
			PORTC |= (1<<1) ; // LED TWO ON
		}
		else{
			PORTC &=~(1<<1 ) ; // LED TWO OFF
		}

	}
}
