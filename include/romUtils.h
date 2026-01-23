#ifndef _ROMUTILS_H_
#define _ROMUTILS_H_

#define RES_BYTE Result
#define RES_VOID Result

#include "Result.h"

typedef enum REGION {
    Global,
    NTSC,
    PAL
} REGION;

typedef struct ROM {
    char *name;
    REGION region;
    uint8_t *romData;
    unsigned long romSize;
    uint8_t *currPos;
} ROM;

RES_VOID readFromFile(const char *filePath, ROM *rom);
RES_VOID writeToFile(const char *filePath, ROM *rom);
RES_BYTE decodeNextIntruction(ROM *rom);

#endif
