#include "Decoder.h"
#include "Result.h"
#include "Rom.h"

#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

ResultInt appendByte(intruction *ins, ResultByte appended) {
    char *err;

    if(ins->pos >= 3) {
        asprintf(&err, "Intruction overtake maximum size (3 bytes)\n");
        return ERR(Int, err);
    }

    if(appended.err != NULL) {
        return ERR(Int, appended.err);
    }
    
    memcpy(&ins->data[ins->pos], &appended.data, 1);
    
    ins->pos += 1;
    
    return OK(Int, ins->pos - 1);
}

ResultInstruction decodeNextIntruction(ROM *rom) {
    intruction ins = {0};
    ResultInt opcodei;
    ResultInt _res[2];

    _TRYGET(ResultInstruction, opcodei, appendByte(&ins, getNextByte(rom)));

    switch (ins.data[opcodei.data]) {
    case (uint8_t)0xEA:
        printf("NOP\n");
        break;
    case (uint8_t)0xA9:
        _TRYGET(ResultInstruction, _res[0], appendByte(&ins, getNextByte(rom)));
        printf("LDA Immediate: arg: %02X\n", ins.data[_res[0].data]);
        break;
    case (uint8_t)0x8d:
        _TRYGET(ResultInstruction, _res[0], appendByte(&ins, getNextByte(rom)));
        _TRYGET(ResultInstruction, _res[1], appendByte(&ins, getNextByte(rom)));
        printf("STA absolute: args: %02X %02X\n", ins.data[_res[0].data], ins.data[_res[1].data]);
        break;
    default:
        printf("%02X \n", ins.data[opcodei.data]);
    }

    return OK(Instruction, ins);
}