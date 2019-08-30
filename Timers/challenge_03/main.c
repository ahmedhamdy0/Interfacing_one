/*
 * write embedded c code for atmega16 to generate a 4KHz Clock using Timer0 PWM Mode .
 * Requirements :
 * 	- Configure the Microcontroller with the internal 8 MHz Clock .
 * 	- Use Timer0 in PWM mode and you choose the required frequancy pre-scaler.
 * 	- Clock Duty Cycle is 50% .
 */

#define F_CPU 8000000UL
#include<avr/io.h>



void Timer0_PWM_Mode_Init(unsigned char duty_cycle)
{
	/*
	 * Fpwm = (F_CPU / (N*256)) ... 4*10^3 = (8*10^6) / (N*256) ..... > N =7.8 ~= 8 ( Prescaler )
	 */
	TCNT0 = 0x00 ;       /* Timer Initial Value */
	OCR0 = duty_cycle ;  /* compare register = duty cycle */
	DDRB |=(1<<3) ;      /* OC0 Pin as Output  */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);/* Fast PWM ,non-inverting mode , 8 Prescaler  */
}
int main(void)
{
	Timer0_PWM_Mode_Init(128) ;
	while(1)
	{

	}
}
