#ifndef BARE_METAL_H
#define BARE_METAL_H

#define BV(bit) (1 << bit)
#define setBit(byte, bit) (byte |= BV(bit))
#define clearBit(byte, bit) (byte &= ~BV(bit))
#define toggleBit(byte, bit) (byte ^= BV(bit))

#endif // BARE_METAL_H