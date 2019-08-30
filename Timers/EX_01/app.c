/*
 * write embedded c code for atmega16 to control a LED using Timer0 .
 * Requirements : -
 * 	- Configure the microcontroller with the internal 1 MHz Clock.
 * 	- LED is connected to Pin0 of PortC .
 * 	- Connect LED using Positive Logic Configuration .
 * 	- Configure the Timer Clock to F_CPU/1024 .
 * 	- Timing should be count using Timer0 in Normal Mode.
 * 	- Toggle the LED every half second .
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#define NUMBER_OVER_FLOWS_HALF_SECOND 2


/*
 * F_CPU = 1 MHz
 * Prescaler = 1024 .... F_Timer = 1/ 1024
 * T for Timer = (1 / (1/1024)) =  1024 micro seconds
 * 1024 / 1000 = 1.024 milli seconds .
 * so , overflow time = 256*1.024 = 262.144 milli seconds .
 * since we need 0.5 seconds .... so , we need to over flow 2 times
 *
 */


unsigned char num_overflows = 0 ;

void Timer0_Init(void)
{

	TCCR0 = (1<<FOC0)| (1<CS00) | (1<<CS02 ) ;	// CS00 , CS02 to set 1024 prescaler , FOC0 ( no PWM = 1 ) .
	TCNT0 = 0x00 ;								// initial value
	TIMSK |= (1<<TOIE0) ;						// enable overflow inturrupt
	TCCR0 &= ~(1<<WGM00);
	TCCR0 &= ~(1<<WGM01) ;
	SREG |= (1<<7) ;						    // global inturrupt enable
}

ISR(TIMER0_OVF_vect)
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
	DDRC |= (1<<0) ;    // LED as Output
	PORTC &= ~(1<<0) ;  // LED OFF at the beginning
	Timer0_Init() ;
	while(1)
	{

	}
}
