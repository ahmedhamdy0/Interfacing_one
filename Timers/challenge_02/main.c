/*
 * write embedded c code for atmega16 to generate a 3 Digital Clocks with Frequency :
 * 10 KHz , 5 KHz , 2.5 KHz using Timer0 CTC Mode .
 * Requirements : -
 * 	- Configure the microcontroller with the internal 8 MHz Clock .
 * 	- Use Timer0 in CTC Mode with Clock equals to F_CPU/8 Clock .
 * 	- The Three Clocks are Output From the First 3 Pins in PortC with Duty Cycle 50% .
 */
#include<avr/io.h>
#include<avr/interrupt.h>
/*
 * get interrupt after the smallest period .
 * -> T for 10 KHz = (1/10) = 0.1 ms
 * 	  T for Timer = 1 / 1MHz = 1 microSecond == 1*10^-3 = 0.001 ms
 * 	  so , to calculate 0.1ms .... ( 0.1 / 0.001) = 100
 * 	  NOTE : -----> (0.1ms/2) ON , (0.1ms/2) OFF , Then Compare Value = 100/2 = 50
 */
unsigned char ticks = 0 ;
void Timer0_CTC_Mode_Init(void)
{
	TCNT0 = 0  ; 		 /*Timer Initial Value */
	OCR0 = 50 ;			 /* Compare Value */
	TIMSK |= (1<<OCIE0) ; /* enable compare match interrupt for timer 0 */
	TCCR0 =(1<<FOC0) |(1<<WGM01)|(1<CS01) ; /* CTC Mode , Prescaler 8 , NonPWM (FOC=1) */
}

ISR(TIMER0_COMP_vect)
{
	ticks++ ;
	PORTC = PORTC ^(1<<0) ;

	if(ticks == 2 )
	{
		PORTC = PORTC ^ (1<<1) ;
	}

	else if(ticks == 4 )
	{
		PORTC = PORTC ^ (1<<1) ;
		PORTC = PORTC ^ (1<<2) ;
		ticks = 0 ;
	}
}

int main(void)
{
	DDRC = 0xFF ;
	PORTC = 0x00 ;
	SREG |=(1<<7) ; /* global interrupt enable */
	Timer0_CTC_Mode_Init() ;
	while(1)
	{

	}
}
