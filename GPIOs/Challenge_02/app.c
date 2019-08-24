/*
  write embeddd c code for atmega16 to control a 7-segment with two push buttons .
  requirements :
    - Configure the microcontroller with the internal 1 MHz Clock.
    - the two switches are connected to Pin 0 , Pin 1 in Port A .
    - connect both switches using Pull Down configuration .
    - the seven segment is connedted to First 4 Pins of Port D.
    - if the switch 1 is pressed just increase the number appeared in the 7 segment display , and if the number reach the
      maximum number [ 9 ]  do nothing .
    - if the switch 2 is pressed just decrease the number appeared in the seven segment display , and if the number reach the
     minimum [ 0 ] do nothing .
 */
#include <avr/io.h>
#include <util/delay.h>
// input 0 , output 1
int main(void)
{
	DDRA &= ~(1<<0) ; // S 1
	DDRA &=~(1<<1) ;  // S 2
	DDRD |= 0x0F ;    // 7-Segment
	unsigned char num = 0x00 ;
	PORTD &= ~((1<<0) | (1<<1) | (1<<2) | (1<<3)) ;
	while(1)
	{
		// check switch one ( pull down )
		if(PINA & (1<<0))
		{
			_delay_ms(20);
			if(PINA & (1<<0) )
			{
				// check overflow
				if((PORTD & 0x0F) != 9)
				{
					num++ ;
					PORTD = (PORTD&0xF0) | (num&0x0F) ;
				}
				while(PINA&(1<<0)){}
			}
		}
		// check witch 2
		else if(PINA & (1<<1))
		{
			_delay_ms(20) ;
			if(PINA & (1<<1 ))
			{
				if( (PORTD & 0x0F) !=0  )
				{
					num-- ;
					PORTD = (PORTD&0xF0) | (num&0x0F) ;
				}
				while(PINA&(1<<1)){} // waith until it relesaed
			}
		}
	}
}
