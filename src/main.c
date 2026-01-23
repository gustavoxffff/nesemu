#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "romUtils.h"
#include "Result.h"

uint8_t mem[65535];
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
    Result r;
    memset(&game, 0, sizeof(ROM));

    if((r = readFromFile(argv[1], &game)).err) {
        fprintf(stderr, "%s\n", r.err);
        return -1;
    }

    // if((r = writeToFile(argv[2], &game)).err) {
    //     fprintf(stderr, "%s\n", r.err);
    //     return -1;
    // }

    // for (unsigned long i = 0; i < game.romSize; i++) {
    //     printf("%02X ", game.romData[i]&0Xff);
    // }

    Result opres = decodeNextIntruction(&game);

    if(!opres.err) {
        printf("%02X ", opres.res.BYTE_RESULT);
    }

    return 0;
}
