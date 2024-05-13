#ifndef CODEC_H
#define CODEC_H

struct request {
    char method[10];
    char resource[256];
    char* body;
};

struct content {
    char* length;
    char* content;
};

struct request parseRequest(char* data);

#endif
