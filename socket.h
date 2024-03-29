#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "asgn2_helper_funcs.h"

// Function to get global variable socket fd
int getSocket();

// Function to set the global variable socket fd
void setSocket(int listenfd);

// Function to reset global variable socket fd to -1
void resetSocket();

// Function to write to global variable socket fd
// Returns number of bytes written upon success, or -1 upon failure
int writeToSocket(char buf[], size_t nbytes);

#endif
