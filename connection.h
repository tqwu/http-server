#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"
#include "request.h"
#include "socket.h"
#include "types.h"
#include "asgn2_helper_funcs.h"

#define BUFSIZE 4096

// Function to continuously listen for incoming connections, and store the file descriptor of
// a valid socket when a new connection is accepted
void acceptConnection(Listener_Socket sock);

// Function to process the connection
void processConnection();

// Function to close the connection
void closeConnection();

#endif
