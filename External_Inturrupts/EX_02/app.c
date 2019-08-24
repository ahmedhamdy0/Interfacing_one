/*
 * write embedded c code using atmega16 to control 8-LEDs by the External Inturrupts INT1.
 * Requirements : -
 * 	- Configure the microcontroller with the internal 1 MHz Clock.
 * 	- 8 LEDs are Connected To Port C .
 * 	- Connect all LEDs using Positive Logic Configuration.
 * 	- a Roll Action is performed using LEDs each LED for half second ,
 * 	  The First LED is lit and roll down to the last LED then back to the First LED.
 * 	  This Operation is Done continuously .
 * 	- Enable the Internal Pull Up resistance at INT1 (Pin PD3) .
 * 	- When the INT1 is Triggered all the LEDs flash five times in five seconds .
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char flag = 0 ;

void INT1_Init(void)
{
	DDRD &= ~(1<<3) ;  		// INT1 as Input Pin
	PORTD |= (1<<3) ; 	 	// internal pull up enable
	SREG = (1<<7) ;   		// 1 - Set Global Inturrupt Enable
	GICR |= (1<<7) ; 		// 2 - Set INT1 Enable Bit
	MCUCR = (1<<ISC11) ; 	// 3 - INT1 Falling Edge
	MCUCR &= ~(1<<ISC10) ;
}


ISR(INT1_vect)
{
	flag = 1 ;
}

int main(void)
{
	DDRC = 0xFF ;   // Port C ( LEDs ) output
	PORTC = 0x01 ;  // LED Initialization
	unsigned char i = 0 ;
	unsigned char temp = 0 ;
	INT1_Init() ;
	while(1)
	{
		if(flag == 0 )
		{
			PORTC = (PORTC<<1) ;
			_delay_ms(500) ;
			if(PORTC == 0x00 )
			{
				PORTC = 0x01 ;
			}
		}
		else if (flag == 1 )
		{
			temp = PORTC ; // to continue from where stopped
			for(i=0 ; i<5 ; i++)
			{
				PORTC = 0xFF ;
				_delay_ms(500) ;
				PORTC = 0x00 ;
				_delay_ms(500) ;
			}
			PORTC = temp ;
			flag = 0 ;
		}
	}
}
