#ifndef __STATUS_H__
#define __STATUS_H__

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "socket.h"
#include "types.h"
#include "asgn2_helper_funcs.h"

typedef enum {
    OK = 200,
    CREATED = 201,
    BAD_REQUEST = 400,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    HTTP_VERSION_NOT_SUPPORTED = 505
} statusCode;

// Function to print the status message to the client
void sendStatus(statusCode status);

// Function to set a Response struct with status message and status message length
// - parameter status: status code
// - parameter method: 1 for GET, 2 for PUT, 0 for all others
// - returns: 0 if status code is valid, -1 if invalid
int setStatus(Response *r, statusCode status, int method);

#endif
