#ifndef __PARSE_H__
#define __PARSE_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <regex.h>
#include "socket.h"
#include "status.h"
#include "types.h"
#include "asgn2_helper_funcs.h"

// Function to get size of file using sys/stat.h
int getFileSize(char *filename);

// Function to parse the request line
// Returns a 0 if a request line was parsed successfully and RequestLine struct was created
// Returns -1 if request line is invalid
int parseRequestLine(RequestLine *rl, char *str_request);

// Function to parse the method
// Function to parse the URI
// Function to parse the version

// Function to parse the header field
// Function to parse the key
// Function to parse the value

// Function to parse the body???

#endif
