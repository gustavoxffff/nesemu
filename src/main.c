#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rom.h"
#include "Decoder.h"
#include "Result.h"

int main(int argc, char **argv) {
    ROM game;
    memset(&game, 0, sizeof(ROM));
    ResultVoid readFile;

    if (argc < 2) {
        fprintf(
            stderr,
            "Usage:\n\tdecode instructions: %s path/to/rom",
            argv[0]
        );

        return -1;
    }

    readFile = readFromFile(argv[1], &game);

    if(readFile.err) {
        fprintf(stderr, "%s\n", readFile.err);
        return -1;
    }
    
    while(1){
        ResultInstruction opres = parseNextIntruction(&game);
        Intruction ins = opres.data;

        printf("%s\n", ins.str);

        free(ins.str);

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
