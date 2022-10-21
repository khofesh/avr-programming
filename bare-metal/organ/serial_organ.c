#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "pin_defines.h"
#include "usart.h"

#define NOTE_DURATION 0xF000

int main(void)
{
    SPEAKER_DDR |= (1 << SPEAKER);
    init_usart();
    print_string("serial organ\r\n");

    // store serial input
    char fromCompy;
    uint16_t currentNoteLength = NOTE_DURATION / 2;
    const uint8_t keys[] = {'a', 'w', 's', 'e', 'd', 'f', 't',
                            'g', 'y', 'h', 'j', 'i', 'k', 'o',
                            'l', 'p', ';', '\''};
    const uint16_t notes[] = {
        G4, Gx4, A4, Ax4, B4, C5, Cx5,
        D5, Dx5, E5, F5, Fx5, G5, Gx5,
        A5, Ax5, B5, C6};
    uint8_t isNote;
    uint8_t i;

    while (1)
    {
        fromCompy = receive_byte();
        transmit_byte('N');

        // play notes
        isNote = 0;
        for (i = 0; i < sizeof(keys); i++)
        {
            if (fromCompy == keys[i])
            {
                play_note(notes[i], currentNoteLength);
                isNote = 1;
                break;
            }
        }

        // handle non-note keys: tempo changes and rests
        if (!isNote)
        {
            if (fromCompy == '[')
            {
                currentNoteLength = NOTE_DURATION / 2;
            }
            else if (fromCompy == ']')
            {
                currentNoteLength = NOTE_DURATION;
            }
            else
            {
                rest(currentNoteLength);
            }
        }
    }

    return 0;
}
