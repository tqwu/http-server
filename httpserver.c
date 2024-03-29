#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "connection.h"
#include "asgn2_helper_funcs.h"

// Function to get command-line arguments: returns a valid port number
int getArgs(int argc, char *argv[]) {

    // Checking for correct number of command line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: ./httpserver <port>\n");
        exit(1);
    }

    // Conversion of provided port number string to an integer
    char *endptr;
    long port;
    port = strtol(argv[1], &endptr, 10);

    // Checking for a valid port number
    if (*endptr != '\0' || port < 1 || port > 65535) {
        fprintf(stderr, "Invalid Port\n");
        exit(1);
    }

    // FIXME: what if conversion goes wrong?
    return (int) port;
}

// Function to create, initialize, and return a listener socket for the port
Listener_Socket bindSocket(int port) {
    Listener_Socket sock;
    int bind = listener_init(&sock, port);

    // If there was an error getting the connection
    if (bind == -1) {
        fprintf(stderr, "Invalid Port\n");
        exit(1);
    }
    return sock;
}

int main(int argc, char *argv[]) {

    // Parse command-line arguments
    int port = getArgs(argc, argv);

    // Create and initialize listener socket for the port
    Listener_Socket sock = bindSocket(port);

    while (1) {

        // Listen and accept incoming connection - only returns when a new connection is accepted
        acceptConnection(sock);

        // Processing connection
        processConnection();

        // Close socket to end connection with client
        closeConnection();
    }

    return 0;
}
