#include "Rom.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Result.h"

unsigned long MAX_FILE_SIZE = 1000000 * sizeof(uint8_t);

ResultVoid readFromFile(const char *filePath, ROM *rom) {
    FILE *file;
    size_t fileSize = 0;
    char *errBuffer;
    
    if (!(file = fopen(filePath, "rb"))) {
        asprintf(&errBuffer, "Error opening %s file!", filePath);
        return ERR(Void, errBuffer);
    }

    fseek(file, 0L, SEEK_END);
    fileSize = ftell(file);

    rewind(file);

    if( fileSize > MAX_FILE_SIZE) {
        asprintf(
            &errBuffer,
            "Rom %s is bigger than limit size: %lu\n",
            filePath,
            MAX_FILE_SIZE
        );
        fclose(file);
        return ERR(Void, errBuffer);
    }

    rom->data = (uint8_t*) malloc(fileSize);

    if (!rom->data) {
        asprintf(&errBuffer, "Failed to allocate rom data\n");
        fclose(file);
        return ERR(Void, errBuffer);
    }

    if ((
        rom->size = fread(rom->data, sizeof(uint8_t), fileSize, file)
    ) < 1) {
        asprintf(&errBuffer, "Failed to read rom data\n");
        free(rom->data);
        fclose(file);
        return ERR(Void, errBuffer);
    }

    rom->currPos = &rom->data[0];
    fclose(file);
    return OKV(Void);
}

ResultVoid writeToFile(const char *filePath, ROM *rom) {
    FILE *file;

    ResultVoid res = {0};

    if(rom->size <= 0) {
        sprintf(res.err, "Room data empty!");
        return res;
    }

    if (!(file = fopen(filePath, "wb"))) {
        sprintf(res.err, "Error opening %s file!", filePath);
        return res;
    }

    fwrite(rom->data, rom->size, 1, file);
    fclose(file);

    return res;
}

ResultByte getNextByte(ROM *rom) {
    if(rom->currPos == rom->data)
        rom->currPos = &rom->data[15]; // Skip 16 bytes header

    rom->currPos++;

    if((unsigned long)(rom->currPos - rom->data) > rom->size) {
        char *err;
        asprintf(&err, "Next byte is ahead rom size\n");
        return ERR(Byte, err);
    }

    return OK(Byte, *rom->currPos);
}
