#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__  // Defining which CPU we are using
#endif

#define F_CPU 16000000UL // ATmega328p Frequency, needed to get correct delays!

#include <avr/io.h> // Standard Input/Output library,contains predefined variables etc
#include <util/delay.h> // library containing delay-function



int main(void) {

    DDRD = 0b01000000; //  Setting Bit to 1 sets the Pin to Output
    
    /*
        Toggling PIN 6 on/off
    */
    for(;;) 
    {
        
        PORTD ^= (1<<6);  // Toggling the sixth bit on and of with a bitwise xor!
        _delay_ms(1000);  // Sleeping for 1 sec  

        
    }
    
    return 0;
}
