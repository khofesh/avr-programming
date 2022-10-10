// #define __AVR_ATmega328P__

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

    // -------- Inits --------- //
    DDRB |= 0b00000001; /* Data Direction Register B:
                          writing a one to the bit
                          enables output. */

    // ------ Event loop ------ //
    while (1)
    {

        PORTB = 0b00000001; /* Turn on first LED bit/pin in PORTB */
        _delay_ms(1000);    /* wait */

        PORTB = 0b00000000; /* Turn off all B pins, including LED */
        _delay_ms(1000);    /* wait */

    }         /* End event loop */
    return 0; /* This line is never reached */
}