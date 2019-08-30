/*
 *	write embedded c code using atmega16 microcontroller to control a 7-Segment using Timer0.
 *	Requirements : -
 *		- Configure the microcontroller with the internal 1 MHz Clock.
 *		- 7-Segment Connected to PortC .
 *		- Configure the Timer clock to F_CPU/256 .
 *		- Timing should be count using Timer0 in Normal Mode .
 *		- Every Second the 7-Segment should be increamented by one .
 *		- If the 7-Segment reached 9 Overflow occur.
 */
#define NUM_OVERFLOWS_ONE_SECOND 123
#include <avr/io.h>
#include <avr/interrupt.h>


unsigned short num_overflows = 0 ;
unsigned char num_to_display = 0 ;

void Timer0_NormalMode_Init(void)
{
	TCNT0 = 0x00 ; 					// Timer Initial Value
	TCCR0 = (1<<FOC0)| (1<<CS02 ) ; // 256 Prescaler
	TIMSK |= (1<<TOIE0) ;		    // enable overflow inturrupt
	// Normal ( Overflow Mode )
	TCCR0 &= ~(1<<WGM00);
	TCCR0 &= ~(1<<WGM01) ;
	SREG |=(1<<7) ; // global inturrupt enable
}

ISR(TIMER0_OVF_vect)
{
	num_overflows++ ;
	if(num_overflows == NUM_OVERFLOWS_ONE_SECOND)
	{
		num_overflows = 0 ;

		if(num_to_display == 9  )
		{
			num_to_display = 0 ;
		}
		else
		{
			num_to_display++ ;
		}
		PORTC = (PORTC&0xF0) | (0x0F&num_to_display) ;
	}
}

int main(void)
{
	DDRC |= 0x0F ;                                 // seven segment as output
	PORTC = (PORTC&0xF0) | (num_to_display&0x0F) ; // seven segment initially displays zero
	Timer0_NormalMode_Init() ;
	while(1)
	{

	}
}


