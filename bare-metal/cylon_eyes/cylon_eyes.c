#define __AVR_ATmega328P__
#include <avr/io.h>
#include <util/delay.h>

#define DELAYTIME 500
#define LED_PORT PORTB
#define LED_PIN PINB
#define LED_DDR DDRB

int main(void)
{
    uint8_t i = 0;
    // set up PB0-PB5 of LED pins for output
    DDRB = 0b00111111;

    while (1)
    {
        while (i < 7)
        {
            // illuminate only i'th pin
            LED_PORT = (1 << i);
            _delay_ms(DELAYTIME);
            // next LED
            i++;
        }

        while (i > 0)
        {
            LED_PORT = (1 << i);
            _delay_ms(DELAYTIME);
            // previous LED
            i--;
        }
    }

    return 0;
}
