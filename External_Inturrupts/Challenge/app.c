/*
 * write embedded c code for atmega16 microcontroller to control a 7-Segment using INT2.
 * Requirements :
 *  - Configure the microcontroller with the internall 1 MHz Clock.
 *  - The 7-Segment is Connected to First 4-Pins of PortC.
 *  - Connect the switch using Pull Down configuration on INT2 ( PB2) Pin .
 *  - when the INT2 is Triggered just Increase the Number Appeared in the 7 Segment Display ,
 *    and if we reach the maximum number [ 9 ] overflow occurs .
 */

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char num = 0x00 ;

void INT2_Init(void)
{
	DDRB &= ~(1<<2) ;     // INT2 Input
	SREG |= (1<<7) ;      // 1 - Set Global Inturrupt Enabe Bit .
	GICR |= (1<<5) ;      // 2 - Set INT2 Enable Bit .
	MCUCSR |= (1<<6) ;    // 3 - Configure INT2 rising edge .
}

ISR(INT2_vect)
{
	// check overflow
	if( num==9 )
	{
		num = 0 ;
	}
	else
	{
		num++ ;
	}
	PORTC = ( (PORTC&0xF0) | (num&0x0F) )  ;
}

int main(void)
{
	DDRC |= 0x0F ;   // seven segment
	PORTC &= 0xF0 ;  // seven segment init
	INT2_Init() ;
	while(1)
	{

	}
}
