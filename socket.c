#include "socket.h"

int socketfd = -1; // Initiate socket file descriptor to -1

int getSocket() {
    return socketfd;
}

void setSocket(int listenfd) {
    socketfd = listenfd;
}

void resetSocket() {
    socketfd = -1;
}

int writeToSocket(char buf[], size_t nbytes) {
    int bytesWritten = write_all(socketfd, buf, nbytes);
    if (bytesWritten == -1) {
        return -1;
    }
    return bytesWritten;
}
