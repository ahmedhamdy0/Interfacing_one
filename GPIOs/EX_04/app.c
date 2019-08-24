/*
  Excerxise 4 :
  ==============================================================================
  write embedded c code for atmega16 to control a LED using a Push  Button .
  requirements :-
    - Configure the Microcontroller with the internal 1 MHz Clock .
    - the Switch is connected to Pin0 in PortB .
    - connect the switch using Internal Pull-Up Configuration .
    - the LED is connected to Pin0 in PortC .
    - connect the LED using Negative Logic Configuration .
    - if the switch is pressed  Toggle the LED .
*/
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  /* Configurations Code */
  DDRC |= (1<<0) ;    // LED PC0 Output
  PORTC |= (1<<0) ;  // LED OFF at the beginning  ( Negative Logic )
  DDRB &= ~(1<<0) ;     // Switch PB0 input
  PORTB |= (1<<0) ;     // enable internal Pull Up
  unsigned char button = 0 ;
  /* Application Code */
  while(1)
  {
    /* check ZERO ( internal pull up ) */
    if( !(PINB & (1<<0)) )
    {
      _delay_ms(20) ; // debouncing
      if( !(PINB & (1<<0)) )
      {
        if(button == 0 )
        {
            PORTC = PORTC ^(1<<0) ; // toggle led
            button = 1 ;
        }
      }
    }else
    {
        button = 0 ;
    }
  }
}
