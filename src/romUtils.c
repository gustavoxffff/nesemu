#include "romUtils.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Result.h"

unsigned long MAX_FILE_SIZE = 1000000 * sizeof(uint8_t);

RES_VOID readFromFile(const char *filePath, ROM *rom) {
    FILE *file;
    size_t fileSize = 0;

    Result res;
    memset(&res, 0, sizeof(Result));

    if (!(file = fopen(filePath, "rb"))) {
        sprintf(res.err, "Error opening %s file!", filePath);
        return res;
    }

    fseek(file, 0L, SEEK_END);
    fileSize = ftell(file);

    rewind(file);

    if( fileSize > MAX_FILE_SIZE) {
        sprintf(
            res.err,
            "Rom %s is bigger than limit size: %lu\n",
            filePath,
            MAX_FILE_SIZE
        );
        fclose(file);
        return res;
    }

    rom->romData = (uint8_t*) malloc(fileSize);

    if (!rom->romData) {
        sprintf(res.err, "Failed to allocate rom data\n");
        fclose(file);
        return res;
    }

    if ((rom->romSize = fread(rom->romData, sizeof(uint8_t), fileSize, file)) < 1) {
        sprintf(res.err, "Failed to read rom data\n");
        free(rom->romData);
        fclose(file);
        return res;
    }

    rom->currPos = &rom->romData[0];
    fclose(file);
    return res;
}

RES_VOID writeToFile(const char *filePath, ROM *rom) {
    FILE *file;

    Result res;
    memset(&res, 0, sizeof(Result));

    if(rom->romSize <= 0) {
        sprintf(res.err, "Room data empty!");
        return res;
    }

    if (!(file = fopen(filePath, "wb"))) {
        sprintf(res.err, "Error opening %s file!", filePath);
        return res;
    }

    fwrite(rom->romData, rom->romSize, 1, file);
    fclose(file);

    return res;
}

RES_BYTE decodeNextIntruction(ROM *rom) {
    Result res;
    res.type = TYPE_BYTE;
    memset(&res, 0, sizeof(Result));

    if(rom->currPos == rom->romData)
        rom->currPos = &rom->romData[15]; // Skip 16 bytes header

    rom->currPos++;

    res.res.BYTE_RESULT = *rom->currPos;

    return res;
}
