#define __AVR_ATmega328P__
#include <avr/io.h>
#include <util/delay.h>

#define DELAYTIME 500

void pov_display(uint8_t oneByte);

int main(void)
{
    // set up all of LED pins for output
    DDRB = 0xff;

    while (1)
    {
        pov_display(0b00001110);
        pov_display(0b00011000);
        pov_display(0b10111101);
        pov_display(0b01110110);
        pov_display(0b00111100);
        pov_display(0b00111100);
        pov_display(0b00111100);
        pov_display(0b01110110);
        pov_display(0b10111101);
        pov_display(0b00011000);
        pov_display(0b00001110);

        PORTB = 0;
        _delay_ms(DELAYTIME);
    }

    return 0;
}

void pov_display(uint8_t oneByte)
{
    PORTB = oneByte;
    _delay_ms(DELAYTIME);
}