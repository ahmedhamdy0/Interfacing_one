/*
 * write embedded c code using atmega16 microcontroller to demonstrate the use of watchdog timer .
 * Requirements : -
 * 	- Configure the microcontroller with the internal 1 MHz Clock.
 * 	- Watchdog timer resets the main program after 2.1 seconds timeout .
 * 	- LED turns ON and OFF after every 2.1 sec due Watchdog timer reset .
 */
#include <avr/io.h>
#include <util/delay.h>
/* Enables Watchdog Timer */
void WDT_ON(void)
{
	WDTCR = (1<<WDE) | (1<<WDP0) | (1<<WDP1) | (1<<WDP2) ;
}
/* Disables Watchdog Timer */
void WDT_OFF(void)
{
	WDTCR = (1<<WDTOE)|(1<<WDE) ;
	WDTCR = 0x00 ;
}

int main(void)
{
	WDT_ON() ;
	DDRD |=(1<<6) ;
	PORTD |=(1<<6) ; /* Turn LED ON */
	_delay_ms(1000) ;
	PORTD &= ~(1<<6) ;/* Turn LED OFF */

	while(1)
	{

	}
}
