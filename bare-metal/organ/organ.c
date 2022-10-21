#include "organ.h"

void play_note(uint16_t wavelength, uint16_t duration)
{
    uint16_t elapsed;

    uint16_t i;

    for (elapsed = 0; elapsed < duration; elapsed += wavelength)
    {
        for (i = 0; i < wavelength; i++)
        {
            _delay_us(1);
        }

        SPEAKER_PORT ^= (1 << SPEAKER);
    }
}

void rest(uint16_t duration)
{
    do
    {
        _delay_us(1);
    } while (--duration);
}
