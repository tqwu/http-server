#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdlib.h>

///////////////////////////////////////////////
// --- Request structs and functions ---
///////////////////////////////////////////////

// Example: HTTP/1.1
typedef struct Version {
    char *type;
    char *num;
} Version;

// Example: GET /foo.txt HTTP/1.1
typedef struct RequestLine {
    char *method;
    char *uri;
    char *version;
    // struct Version *version;
} RequestLine;

// Example: Content-Length: 12
typedef struct Header {
    char *name;
    char *value;
} Header;

// Example: GET /foo.txt HTTP/1.1 Content-Length: 12 Hello world!
typedef struct {
    struct RequestLine *requestLine;
    struct Header *header; // The header field is an optional field
    char *body; // The message body is an optional field
} Request;

void freeRequestLine(RequestLine *rl);

///////////////////////////////////////////////
// --- Response structs and functions ---
///////////////////////////////////////////////

typedef struct Response {
    // char msg[128];
    char *msg;
    int msglen;
} Response;

void freeResponse(Response *r);

#endif
