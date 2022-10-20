#define __AVR_ATmega328P__
/*
  Quick and dirty functions that make serial communications work.

  Note that receive_byte() blocks -- it sits and waits _forever_ for
   a byte to come in.  If you're doing anything that's more interesting,
   you'll want to implement this with interrupts.

   initUSART requires BAUDRATE to be defined in order to calculate
     the bit-rate multiplier.  9600 is a reasonable default.

  May not work with some of the older chips:
    Tiny2313, Mega8, Mega16, Mega32 have different pin macros
    If you're using these chips, see (e.g.) iom8.h for how it's done.
    These old chips don't specify UDR0 vs UDR1.
    Correspondingly, the macros will just be defined as UDR.
*/

#include <avr/io.h>
#include "usart.h"
#include <util/setbaud.h>

void init_usart(void)
{                         /* requires BAUD */
    UBRR0H = UBRRH_VALUE; /* defined in setbaud.h */
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif
    /* Enable USART transmitter/receiver */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
}

void transmit_byte(uint8_t data)
{
    /* Wait for empty transmit buffer */
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data; /* send data */
}

uint8_t receive_byte(void)
{
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait for incoming data */
    return UDR0;                         /* return register value */
}

/* Here are a bunch of useful printing commands */

void print_string(const char myString[])
{
    uint8_t i = 0;
    while (myString[i])
    {
        transmit_byte(myString[i]);
        i++;
    }
}

void read_string(char myString[], uint8_t maxLength)
{
    char response;
    uint8_t i;
    i = 0;
    while (i < (maxLength - 1))
    { /* prevent over-runs */
        response = receive_byte();
        transmit_byte(response); /* echo */
        if (response == '\r')
        { /* enter marks the end */
            break;
        }
        else
        {
            myString[i] = response; /* add in a letter */
            i++;
        }
    }
    myString[i] = 0; /* terminal NULL character */
}

void print_byte(uint8_t byte)
{
    /* Converts a byte to a string of decimal text, sends it */
    transmit_byte('0' + (byte / 100));       /* Hundreds */
    transmit_byte('0' + ((byte / 10) % 10)); /* Tens */
    transmit_byte('0' + (byte % 10));        /* Ones */
}

void print_word(uint16_t word)
{
    transmit_byte('0' + (word / 10000));       /* Ten-thousands */
    transmit_byte('0' + ((word / 1000) % 10)); /* Thousands */
    transmit_byte('0' + ((word / 100) % 10));  /* Hundreds */
    transmit_byte('0' + ((word / 10) % 10));   /* Tens */
    transmit_byte('0' + (word % 10));          /* Ones */
}

void print_binary_byte(uint8_t byte)
{
    /* Prints out a byte as a series of 1's and 0's */
    uint8_t bit;
    for (bit = 7; bit < 255; bit--)
    {
        if (bit_is_set(byte, bit))
            transmit_byte('1');
        else
            transmit_byte('0');
    }
}

char nibble_to_hex_character(uint8_t nibble)
{
    /* Converts 4 bits into hexadecimal */
    if (nibble < 10)
    {
        return ('0' + nibble);
    }
    else
    {
        return ('A' + nibble - 10);
    }
}

void print_hex_byte(uint8_t byte)
{
    /* Prints a byte as its hexadecimal equivalent */
    uint8_t nibble;
    nibble = (byte & 0b11110000) >> 4;
    transmit_byte(nibble_to_hex_character(nibble));
    nibble = byte & 0b00001111;
    transmit_byte(nibble_to_hex_character(nibble));
}

uint8_t get_number(void)
{
    // Gets a numerical 0-255 from the serial port.
    // Converts from string to number.
    char hundreds = '0';
    char tens = '0';
    char ones = '0';
    char thisChar = '0';
    do
    { /* shift over */
        hundreds = tens;
        tens = ones;
        ones = thisChar;
        thisChar = receive_byte(); /* get a new character */
        transmit_byte(thisChar);   /* echo */
    } while (thisChar != '\r');    /* until type return */
    return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}
