/*
 * write embedded c code for atmega16 microcontroller to control LED brightness using Fast PWM.
 * requirements : -
 * 	- Configure the micocontroller with the internal 1 MHz Clock.
 * 	- Use Timer0 in PWM with Clock = F_CPU / 8 .
 * 	- Generate the same PWM signal like the previous example with different duty cycles to control the
 * 	  brightness of the LED .
 */

#include <avr/io.h>
#include <util/delay.h>

void Timer0_PWM_Init(unsigned char duty_cycle )
{
	TCNT0 = 0x00 ;        /* Timer Initial Value */
	OCR0 = duty_cycle ;   /* Compare Value       */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);/* Fast PWM ,non-inverting mode , 8 Prescaler  */
	DDRB |=(1<<3) ; 	  /* OC0 Pin as Output */
}

int main(void)
{
	unsigned char i = 0 ;
	while(1)
	{
		for(i=0 ; i<256 ; i++)
		{
			Timer0_PWM_Init(i) ;
			_delay_ms(10) ;
		}
		_delay_ms(100);
		for(i = 255 ; i>=0 ; i--)
		{
			Timer0_PWM_Init(i) ;
			_delay_ms(10);
		}
	}
}


