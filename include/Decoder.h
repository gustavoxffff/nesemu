#ifndef _DECODER_H_
#define _DECODER_H_

#include "Result.h"
#include "Rom.h"

typedef struct intruction {
    uint8_t data[3];
    unsigned short pos;
}intruction;

#ifndef RESULT_INSTRUCTION
#define RESULT_INSTRUCTION
DEFINE_RESULT(intruction, Instruction)
#endif

#ifndef RESULT_INT
#define RESULT_INT
DEFINE_RESULT(int, Int)
#endif

#ifndef RESULT_BYTE
#define RESULT_BYTE
DEFINE_RESULT(uint8_t, Byte)
#endif

#ifndef RESULT_BYTEPTR
#define RESULT_BYTEPTR
DEFINE_RESULT(uint8_t*, BytePtr)
#endif

ResultInstruction decodeNextIntruction(ROM *rom);

#endif