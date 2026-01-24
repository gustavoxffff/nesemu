#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdint.h>

#define byte uint8_t

byte mem[65535];

const byte *ram      = mem + 0x0000;
const byte ram_size  = (byte)0x0800;

const byte *ppu      = mem + 0x2000;
const byte ppu_size  = (byte)0x0008;

const byte *pulse1   = mem + 0x4000;
const byte pulse1_size = (byte)0x0008;
const byte *pulse2   = mem + 0x0800;
const byte pulse2_size = (byte)0x0008;

const byte *unmapped = mem + 0x4020;
const byte unmapped_size = (byte)0x4020;

#endif