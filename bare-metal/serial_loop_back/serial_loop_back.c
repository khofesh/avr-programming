#define __AVR_ATmega328P__
/*
 * A simple test of serial-port functionality.
 * Takes in a character at a time and sends it right back out,
 * displaying the ASCII value on the LEDs.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "pin_defines.h"

int main(void)
{
    char serialCharacter;

    // init
    LED_DDR = 0xff;
    init_usart();
    print_string("hola mundo!\r\n");

    while (1)
    {
        serialCharacter = receive_byte();
        transmit_byte(serialCharacter);
        // print_binary_byte(serialCharacter);
        // print_string("\r\n");
        LED_PORT = serialCharacter;
    }

    return 0;
}