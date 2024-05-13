#include <asm-generic/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "server.h"

void spawnThread(int socketFD);

int main(int argc, char** argv) {
    int serverFD, clientSock;
    int opt = 1;
    struct sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);

    serverFD = socket(AF_INET, SOCK_STREAM, 0);
    if(serverFD < 0) {
        printf("ERROR CREATING SOCKET, EXITING\n");
        return 1;
    }
    setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    int err = bind(serverFD, (struct sockaddr*)&addr, sizeof(addr));
    if(err < 0) {
        printf("ERROR CREATING SOCKET, EXITING\n");
        return 1;
    }

    listen(serverFD, 5);
    while(1){
        clientSock = accept(serverFD, (struct sockaddr*)&addr, &addrLen);
        if(clientSock < 0) {
            printf("Connection Error");
            continue;
        }
        spawnThread(clientSock);
    }

    return 0;
}


void spawnThread(int socketFD) {
    pthread_t thread_id;
    int fd = socketFD;
    int err = pthread_create(&thread_id, NULL, handleConnection, (void * )&fd);
    if(err != 0) {
        printf("Failed to create thread");
        close(socketFD);
    }
    pthread_detach(thread_id);
}
