/*
 * write embedded c code for atmega16 to control a LED using Timer0 .
 * Requirements : -
 * 	- Configure the microcontroller with the internal 1 MHz Clock.
 * 	- LED is connected to Pin0 of PortC .
 * 	- Connect LED using Positive Logic Configuration .
 * 	- Configure the Timer Clock to F_CPU/1024 .
 * 	- Timing should be count using Timer0 in CTC Mode (Clear Timer on Compare) .
 * 	- Toggle the LED every half second .
 */


#define NUMBER_OVER_FLOWS_HALF_SECOND 2
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char num_overflows = 0 ;
/* For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
 * so we just need 250 counts to get 250ms every overflow. put initial timer counter=0
 * and output compare register=250 0 --> 250 (250ms per overflow)
 * so we need timer to overflow 2 times to get a 0.5 second
 */

void Timer0_CTC_Init(unsigned char tick )
{
	TCNT0 = 0x00 ;              // timer initial value
	OCR0 = tick ; 				 // compare value ( Output Compare Register )
	TCCR0 = (1<<FOC0)| (1<CS00) | (1<<CS02 ) | (1<<WGM01) ;
	TIMSK |= (1<<OCIE0) ; 		// Timer 0 Output Compare Inturrupt Enable
}

ISR(TIMER0_COMP_vect)
{
	num_overflows++ ;
	if(num_overflows == NUMBER_OVER_FLOWS_HALF_SECOND)
	{
		PORTC = PORTC ^(1<<0) ; // led toggling
		num_overflows = 0 ;
	}
}

int main(void)
{
	DDRC  |= (1<<PC0);         // configure the led pin to be output pin.
	PORTC &= ~(1<<PC0);        // LED is off at the beginning(Positive Logic).
	Timer0_CTC_Init(250) ;
	SREG  |= (1<<7);           // enable global interrupts in MC.
	while(1)
	{

	}
}
























