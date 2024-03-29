#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"
#include "socket.h"
#include "status.h"
#include "types.h"
#include "asgn2_helper_funcs.h"

#define BUFSIZE 4096

// Function to process a GET request
// Returns 0 if GET request was successful and 200 status was returned
// Returns -1 if request failed
int requestGET(RequestLine *rl);

// TODO: Function for PUT request

#endif
