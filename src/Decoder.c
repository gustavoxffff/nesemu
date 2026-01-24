#include "Decoder.h"
#include "Result.h"
#include "Rom.h"

#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

ResultInt appendByte(Intruction *ins, ResultByte appended) {
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

ResultInstruction parseNextIntruction(ROM *rom) {
    Intruction ins = {0};
    ResultInt opcodei;
    ResultInt _res[2];

    _TRYGET(ResultInstruction, opcodei, appendByte(&ins, getNextByte(rom)));

    switch (ins.data[opcodei.data]) {
    case (uint8_t)0xEA:
        asprintf(&ins.str, "NOP");
        break;
    case (uint8_t)0xA9:
        _TRYGET(ResultInstruction, _res[0], appendByte(&ins, getNextByte(rom)));
        asprintf(&ins.str,"LDA Immediate: arg: %02X", ins.data[_res[0].data]);
        break;
    case (uint8_t)0x8d:
        _TRYGET(ResultInstruction, _res[0], appendByte(&ins, getNextByte(rom)));
        _TRYGET(ResultInstruction, _res[1], appendByte(&ins, getNextByte(rom)));
        asprintf(&ins.str,"STA absolute: args: %02X %02X", ins.data[_res[0].data], ins.data[_res[1].data]);
        break;
    default:
        asprintf(&ins.str,"%02X", ins.data[opcodei.data]);
    }

    return OK(Instruction, ins);
}


