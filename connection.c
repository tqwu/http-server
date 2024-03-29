#include "connection.h"

void acceptConnection(Listener_Socket sock) {
    while (1) {
        int listenfd = listener_accept(&sock);
        if (listenfd > 0) {
            setSocket(listenfd);
            return;
        }
    }
}

void closeConnection() {
    // printf("Closing connection...\n");
    int socketfd = getSocket();
    if (close(socketfd) == 1) {
        fprintf(stderr, "Error: There was an error closing the socket connection.\n");
        exit(1);
    }
}

void processConnection() {

    int socketfd = getSocket();
    if (socketfd == -1) {
        fprintf(stderr, "Error: there was an error establishing a socket connection.\n");
        exit(1);
    }

    char buf[BUFSIZE + 1]; // +1 for null terminating character

    // Allocating memory for a RequestLine struct
    RequestLine *rl = malloc(sizeof(RequestLine));

    ssize_t bytesRead = read_until(socketfd, buf, 2048, "\r\n\r\n");
    buf[bytesRead] = '\0'; // Null terminate buffer

    // If read failed or request timed out: send 400
    if (bytesRead == -1) {
        statusCode status = BAD_REQUEST;
        sendStatus(status);
        free(rl); // Only rl has been allocated so far
        return;
    }

    // If REGEX doesn't match a valid request line: send 400
    else if (parseRequestLine(rl, buf) == -1) {
        free(rl); // Only rl has been allocated if parseRequestLine returns -1
        return;
    }

    // Otherwise:
    // Check if request is a GET: if so, read from file and send 200
    else {
        char method[4];
        strncpy(method, rl->method, 3);
        method[3] = '\0';

        // If method is GET, try to process the GET request
        if ((strlen(rl->method) == 4) && (strcmp(method, "GET") == 0)) {
            if (requestGET(rl) == -1) {
                freeRequestLine(rl);
                return;
            }
        }
        // If the function is not GET, send 501
        else if (strcmp(method, "GET") != 0) {
            statusCode status = NOT_IMPLEMENTED;
            sendStatus(status);
            freeRequestLine(rl);
            return;
        }

        // TODO: PUT method
        // TODO: what happens if a user inputs a non-implemented method?
    }

    freeRequestLine(rl);
    return;
}

// Testing request struct
// char *type = "HTTP/";
// char *num = "1.1";
// char *method = "GET";
// char *uri = "/index.html";
// char *name = "Key:";
// char *value = "Value";
// char *body = "Body";

// char *type = NULL;
// char *num = NULL;
// char *method = NULL;
// char *uri = NULL;
// char *name = NULL;
// char *value = NULL;
// char *body = NULL;

// Version testVersion = { type, num };
// RequestLine testRequestLine = { method, uri, &testVersion };

// Header testHeader = { name, value };
// Request testRequest = { &testRequestLine, &testHeader, body };

// printf("Request-Line: %s %s %s %s\n", testRequest.requestLine->method,
//     testRequest.requestLine->uri, testRequest.requestLine->version->type,
//     testRequest.requestLine->version->num);

// printf("Header-Field: %s %s %s\n", testRequest.header->name, testRequest.header->value,
//     testRequest.body);
