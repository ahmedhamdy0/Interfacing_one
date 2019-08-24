/*
  write embedded c code for atmega16 to control 7-Segment using a Push Button .
  requirements : -
  ==============================================================================
  - configure the micro-controller with the internal 1MHz Clock.
  - the switch is connected to Pin4 in PortD.
  - connect the switch using Pull Down configuration.
  - the 7-segment is connected to first 4 Pins of PortC.
  - if the switch is pressed just increase the number apperaed in the 7-Segment display ,
    and if we reach the maximum number [ 9 ] overflow occurs .
 */
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRD &= ~(1<<PD4) ;  // switch is input
	DDRC |= 0x0F ;       // 7-segment output
	PORTC &= ~(  (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3)  ); // initialize the 7-segment ZERO at the beginning
	unsigned char num = 0 ;

	while(1)
	{
		// check button ( check ones - pull down - )
		if(PIND & (1<<PD4) )
		{
			_delay_ms(20) ; // debouncing
			if( PIND & (1<<PD4) )
			{
				// check overflow
				if( (PORTC & 0x0F) == 9 )
				{
					num = 0 ;
					PORTC = (PORTC & 0xF0) | (num & 0x0F);
				}
				else{
					num++ ;
					PORTC = (PORTC & 0xF0) | (num & 0x0F);
				}
			}
			while(PIND &(1<<PD4))
			{
				// wait until the switch is released
			}
		}
	}
}
