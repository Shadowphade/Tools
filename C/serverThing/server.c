#include <sys/socket.h>
#include "server.h"
#include "codec.h"

void* handleConnection(void *clientFD) {
    int *sockFd = (int *) clientFD;
    char buffer[1024] = {'0'};
    printf("File Descriptor: %d", *sockFd);
    int err = read(*sockFd, buffer, 1024 - 1);
    //printf("ERR VAL: %d\nBUFFER: %s\n", err, buffer);

    struct request req = parseRequest(buffer);

    printf("Method: %s\nResource: %s\nBody: %s\n", req.method, req.resource, req.body);

    tearDownConnection(*sockFd);
    return 0;
}

void tearDownConnection(int clientFD) {
    close(clientFD);
}
