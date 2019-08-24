/*
  Challenge 1 : -
  ==============================================================================
  write embedded c code for Atmega16 to control 8-LEDs .
  requirements : -
    - configure the micro-controller with the internal 1MHz Clock.
    - 8 LEDs are connected to PORTC.
    - connect all LEDs using Positive Logic configuration .
    - A Roll Action is Perform using the LEDs each LED for half second ,
      The First LED is lit and roll down to the last LED then back to the First LED.
      This Operation is Done Continously .
*/
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRC = 0xFF ;  // all port c pins are output
  PORTC = 0x00 ; // initially OFF
  unsigned char counter = 0x01 ; // First LED is On at the beginning
  while(1)
  {
    for(counter = 0 ; counter < 8 ; counter++)
    {
      PORTC = (1<<counter) ;
      _delay_ms(500) ;
    }

  }
}
/***************************/
/***** Another Solutin *****/
/***************************/
// #include <avr/io.h>
// #include <util/delay.h>
//
// int main(void)
// {
// 	DDRC  = 0xFF;	// Configure all PORTC pins as output pins
// 	PORTC = 0x01;   // First led is on at the beginning (Positive Logic configuration)
//
// 	while(1)
// 	{
//
// 		_delay_ms(500);
// 		PORTC = (PORTC<<1); //every time only one led is ON
// 		if(PORTC == 0x00)
// 		{
// 			/* In case PORTC equals ZERO after 8 shifts
// 			 * turn on the first led to start rolling again */
// 			PORTC = 0x01;
// 		}
// 	}
// }
