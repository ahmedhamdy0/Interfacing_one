/*
 * write embedded c code for atmega16 to control a LED using the external inturrupt INT0.
 * Requirements : -
 * 	- Configure the Microcontroller with the internal 1 MHz Clock.
 * 	- LED is connected to Pin0 in Port C.
 * 	- Connect the LED using Negative Logic Configuration .
 * 	- Connect Push Button with Pull Down configuration at INT0 (Pin PD2).
 * 	- when the INT0 is triggered just Toggle The LED .
 */

#include <avr/io.h>
#include <avr/interrupt.h>


/* INT0 enable and configurations */
void INT0_Init(void)
{
	SREG &= ~(1<<7) ;            // Reset Global Inturrupt Enable Bit
	DDRD &= ~(1<<2) ;            // INT0 Input
	SREG |= (1<<7) ;             // 1 - Set Global Inturrupt Enable Bit
	GICR |=(1<<6) ;              // 2 - Set INT0 Enable Bit
	MCUCR |= (1<<0) | (1<<1) ;   //3 - Rising Edge
}

/* ISR For INT0 */
ISR(INT0_vect)
{
	PORTC = PORTC ^(1<<0) ; // Toggle LED
	GIFR |= (1<<6) ;         // Clear Flag
}


int main(void){
	DDRC |= (1<<0) ;   // LED output
	PORTC &= ~(1<<0) ; // LED OFF at the Beginning
	INT0_Init() ;
	while(1)
	{

	}
}


