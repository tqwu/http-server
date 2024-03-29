#include "status.h"

void sendStatus(statusCode status) {
    Response *r = malloc(sizeof(Response));
    setStatus(r, status, 1);
    int socketfd = getSocket();
    ssize_t bytesWritten = write_all(socketfd, r->msg, r->msglen);
    // If response was unable to be written, free response and return
    if (bytesWritten == -1) {
        freeResponse(r);
        return;
    }
    freeResponse(r);
}

static void setFields(Response *r, char *message) {
    int length = strlen(message);
    r->msg = malloc(length + 1);
    strncpy(r->msg, message, length);
    r->msg[length] = '\0';
    r->msglen = length;
}

int setStatus(Response *r, statusCode status, int method) {
    switch (status) {
    case OK:
        if (method == 1) {
            setFields(r, "HTTP/1.1 200 OK\r\n");
            return 0;
        } else if (method == 2) {
            setFields(r, "HTTP/1.1 200 OK\r\nContent-Length: 3\r\n\r\nOK\n");
            return 0;
        }

    case CREATED:
        setFields(r, "HTTP/1.1 201 Created\r\nContent-Length: 8\r\n\r\nCreated\n");
        return 0;

    case BAD_REQUEST:
        setFields(r, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n");
        return 0;

    case FORBIDDEN:
        setFields(r, "HTTP/1.1 403 Forbidden\r\nContent-Length: 10\r\n\r\nForbidden\n");
        return 0;

    case NOT_FOUND:
        setFields(r, "HTTP/1.1 404 Not Found\r\nContent-Length: 10\r\n\r\nNot Found\n");
        return 0;

    case INTERNAL_SERVER_ERROR:
        setFields(r,
            "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server "
            "Error\n");
        return 0;

    case NOT_IMPLEMENTED:
        setFields(r, "HTTP/1.1 501 Not Implemented\r\nContent-Length: 16\r\n\r\nNot Implemented\n");
        return 0;

    case HTTP_VERSION_NOT_SUPPORTED:
        setFields(r, "HTTP/1.1 505 Version Not Supported\r\nContent-Length: 22\r\n\r\nVersion Not "
                     "Supported\n");
        return 0;

    default: return -1;
    }

    return -1;
}
