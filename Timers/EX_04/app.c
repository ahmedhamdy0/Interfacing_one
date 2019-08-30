/*
 *	Write embedded c code for atmega16 to generate a 500 Hz Clock using PWM.
 *	Requirements : -
 *		- Configure the microcontroller with the internal 1 MHz Clock.
 *		- Use Timer 0 in PWM Mode .
 *		- Clock Duty Cycle is 50%
 *		- Clock Duty Cycle is 25%
 */

#include<avr/io.h>
#include<util/delay.h>
/*
 * Fpwm = (F_CPU / (N*256)) ... 500 = (1*10^6) / (N*256) ..... > N = 8 ( Prescaler )
 */
void Timer0_PWM_Mode_Init(unsigned char duty)
{
	TCNT0 = 0x00 ;	/* Timer Initial Value */
	OCR0 = duty ;   /* Compare Value       */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);/* Fast PWM ,non-inverting mode , 8 Prescaler  */
}

int main(void)
{
	DDRB = (1<<3) ; 			/* OC0 as Output */
	Timer0_PWM_Mode_Init(128) ; /* 50% Duty Cycle (0.50*256) */
	_delay_ms(2000) ;
	Timer0_PWM_Mode_Init(64) ; /* 25% Duty Cycle (0.25*256) */


	while(1)
	{

	}
}
