#define __AVR_ATmega328P__
#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAYTIME 500
#define LED_PORT PORTB
#define LED_DDR DDRB

int main(void)
{
    clock_prescale_set(clock_div_8);

    uint8_t i;
    uint8_t repetitions;
    uint8_t whichLED;
    uint16_t randomNumber = 0x1234;

    // init
    LED_DDR = 0xff;

    while (1)
    {
        // go left
        for (i = 0; i < 7; i++)
        {
            // turn on the i-th pin
            LED_PORT |= (1 << i);
            _delay_ms(DELAYTIME);
        }

        for (i = 0; i < 7; i++)
        {
            // turn off the i-th pin
            LED_PORT &= ~(1 << i);
            _delay_ms(DELAYTIME);
        }
        _delay_ms(5 * DELAYTIME);

        for (i = 7; i < 63; i--)
        {
            LED_PORT |= (1 << i);
            _delay_ms(DELAYTIME);
        }

        for (i = 7; i < 63; i--)
        {
            LED_PORT &= ~(1 << i);
            _delay_ms(DELAYTIME);
        }
        _delay_ms(5 * DELAYTIME);

        // toggle random bits for a while

        for (repetitions = 0; repetitions < 75; repetitions++)
        {
            // random number generator
            randomNumber = 2053 * randomNumber + 13849;
            // low three bits from high byte
            whichLED = (randomNumber >> 8) & 0b00000111;
            // toggle LED
            LED_PORT ^= (1 << whichLED);
            _delay_ms(DELAYTIME);
        }

        LED_PORT = 0;
        _delay_ms(5 * DELAYTIME);
    }

    return 0;
}
