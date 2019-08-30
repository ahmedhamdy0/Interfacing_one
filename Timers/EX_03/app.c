/* write embedded c code for atmega16 to generate a 2 KHz Clock using Timer 0 CTC Mode.
 * Requirents : -
 * 	- Configure the Microcontroller with the internal 1 MHz Clock.
 * 	- Use Timer 0 in CTC Mode with Clock equals to F_CPU Clock.
 * 	- Clock Duty Cycle is 50% .
 */

#include <avr/io.h>

void Timer0_CTC_Init(void)
{
	/*
	 * 	/* Configure timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. Toggle OC0 on compare match COM00=1 & COM01=0
	 * 4. clock = CPU clock CS00=1 CS01=0 CS02=0
	 ---------------------------------------------------
	 *
	 * TCNT0 =  0   .... initial value
	 * FOC0  =  1  .... NO PWM
	 * CS00  =  1  .... NO Prescaler
	 * WGM01 =  1  .... CTC Mode
	 * COM00 =  1  .... Toggle on match
 	 */
	TCNT0 = 0 ;
	OCR0 = 250 ;
	DDRB = DDRB | (1<<PB3); // OC0 Pin as output pin
	TCCR0 = (1<<FOC0) | (1<<CS00) | (1<<WGM01) | (1<<COM00) ;

}

int main(void)
{
	Timer0_CTC_Init() ;
	while(1)
	{

	}
}




