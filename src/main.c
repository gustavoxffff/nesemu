#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rom.h"
#include "Decoder.h"
#include "Result.h"

int cpuHz = 1790000000;

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(
            stderr,
            "Usage: %s path/to/rom path/to/out\n",
            argv[0]
        );

        return -1;
    }

    ROM game;
    memset(&game, 0, sizeof(ROM));
    ResultVoid res = readFromFile(argv[1], &game);

    if(res.err) {
        fprintf(stderr, "%s\n", res.err);
        exit(-1);
    }

    // if((r = writeToFile(argv[2], &game)).err) {
    //     fprintf(stderr, "%s\n", r.err);
    //     return -1;
    // }

    // for (unsigned long i = 0; i < game.romSize; i++) {
    //     printf("%02X ", game.romData[i]&0Xff);
    // }

    while(1){
        ResultInstruction opres = decodeNextIntruction(&game);

        if(opres.err != NULL) {
            fprintf(stderr, "%s", opres.err);
            exit(-1);
        }

        if (game.currPos >= &game.data[193]) {
            break;
        }
    }

    return 0;
}
