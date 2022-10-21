#ifndef ORGAN_H
#define ORGAN_H

#define __AVR_ATmega328P__

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "pin_defines.h"

void play_note(uint16_t wavelength, uint16_t duration);
void rest(uint16_t duration);

#endif // ORGAN_H