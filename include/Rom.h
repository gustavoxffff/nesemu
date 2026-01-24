#ifndef _ROMUTILS_H_
#define _ROMUTILS_H_

#include "Result.h"

#ifndef RESULT_BYTE
#define RESULT_BYTE
DEFINE_RESULT(uint8_t, Byte)
#endif

#ifndef RESULT_BYTEPTR
#define RESULT_BYTEPTR
DEFINE_RESULT(uint8_t*, BytePtr)
#endif

typedef enum REGION {
    Global,
    NTSC,
    PAL
} REGION;

typedef struct ROM {
    char *name;
    REGION region;
    uint8_t *data;
    unsigned long size;
    uint8_t *currPos;
} ROM;

ResultVoid readFromFile(const char *filePath, ROM *rom);
ResultVoid writeToFile(const char *filePath, ROM *rom);
ResultByte getNextByte(ROM *rom);

#endif
