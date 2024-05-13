#include <stdlib.h>
#include <string.h>
#include "codec.h"

struct request parseRequest(char* buffer) {
    struct request output;

    int methodStringSize = 0;
    int resourceStringSize = 0;
    char currChar = buffer[0];
    int currIndex = 0;
    char* tmpBuffer = malloc(sizeof(buffer));
    strcpy(tmpBuffer, buffer);
    char* strtok()


    for(; currChar != ' '; currIndex++) {
        currChar = buffer[currIndex];
        output.method[methodStringSize] = currChar;
        methodStringSize++;
    }
    for(; currChar != ' '; currIndex++) {
        currChar = buffer[currIndex];
        output.resource[resourceStringSize] = currChar;
        resourceStringSize++;
    }

    for(; currChar != '\0'; currIndex++) {
        currChar = buffer[currIndex];
        if(currChar == '\r' && buffer[currIndex + 1] == '\n') {
            int size = 0;
            char seekChar = ' ';
            for(int i = currIndex + 1; seekChar != '\0'; i++){
                seekChar = buffer[i];
                size++;
            }
            output.body = malloc(size * sizeof(char)); // CAUTION REMEMBER TO FREE WHEN OBJECT LIFETIME IS OVER!!!!!!!!
            for(int i = currIndex + 1; seekChar != '\0'; i++){
                output.body[i - currIndex + 1] = buffer[i];
            }
        }
    }

    return output;
}
