#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* handleConnection(void *clientFD);
void tearDownConnection(int clientFD);


#endif
